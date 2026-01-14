use std::{collections::HashMap, num::ParseIntError, str::FromStr};
use thiserror::Error;

#[derive(Debug, Error)]
pub enum ParseError {
    #[error("EventError")]
    ParseEventError,
    #[error("TimeError")]
    ParseTimeError,
    #[error("LogError")]
    ParseLogError,
    #[error(transparent)]
    Invalid(#[from] ParseIntError),
}

#[derive(Debug, Eq, PartialEq)]
pub enum Event {
    StartShift(u32),
    FallAsleep,
    WakeUp,
}

#[derive(Debug, Eq, PartialEq, Clone, Copy, Ord, PartialOrd)]
pub struct Time {
    year: u32,
    month: u32,
    day: u32,
    hour: u32,
    minute: u32,
}

impl Time {
    #[cfg(test)]
    pub const fn new(year: u32, month: u32, day: u32, hour: u32, minute: u32) -> Self {
        Self {
            year,
            month,
            day,
            hour,
            minute,
        }
    }
}
impl FromStr for Time {
    type Err = ParseError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Ok(Self {
            year: s[0..4].parse().map_err(|_| ParseError::ParseTimeError)?,
            month: s[5..7].parse().map_err(|_| ParseError::ParseTimeError)?,
            day: s[8..10].parse().map_err(|_| ParseError::ParseTimeError)?,
            hour: s[11..13].parse().map_err(|_| ParseError::ParseTimeError)?,
            minute: s[14..16].parse().map_err(|_| ParseError::ParseTimeError)?,
        })
    }
}

impl FromStr for Event {
    type Err = ParseError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let event = match s {
            "falls asleep" => Self::FallAsleep,
            "wakes up" => Self::WakeUp,
            _ => {
                let id = s
                    .strip_prefix("Guard #")
                    .and_then(|s| s.strip_suffix(" begins shift"))
                    .ok_or(ParseError::ParseEventError)?
                    .parse::<u32>()
                    .map_err(|_| ParseError::ParseEventError)?;
                Self::StartShift(id)
            }
        };
        Ok(event)
    }
}

#[derive(Copy, Clone)]
pub struct Guard {
    id: u32,
    minutes_asleep: u32,
    frequency: [u16; 60],
}

impl Guard {
    fn new(id: u32) -> Self {
        Self {
            id,
            minutes_asleep: 0,
            frequency: [0; 60],
        }
    }

    fn register_sleep_time(&mut self, start: u32, end: u32) {
        self.minutes_asleep += end.checked_sub(start).expect("Time order");
        for m in start..end {
            self.frequency[m as usize] += 1;
        }
    }
}

#[derive(Debug, PartialEq, Eq)]
pub struct ParseGuardError;

#[derive(Debug, Eq, PartialEq)]
pub struct LogEntry {
    time: Time,
    event: Event,
}

impl LogEntry {
    #[cfg(test)]
    fn new(time: Time, event: Event) -> Self {
        Self { time, event }
    }
}

impl FromStr for LogEntry {
    type Err = ParseError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (time, event) = s
            .strip_prefix("[")
            .and_then(|s| s.split_once("] "))
            .ok_or(ParseError::ParseLogError)?;

        Ok(Self {
            time: time.parse()?,
            event: event.parse()?,
        })
    }
}
pub fn parse_data(input: &str) -> Result<Vec<LogEntry>, ParseError> {
    let mut parsed: Vec<LogEntry> = input
        .lines()
        .map(|s| s.parse::<LogEntry>())
        .collect::<Result<_, _>>()?;
    parsed.sort_by_key(|l| l.time);
    Ok(parsed)
}

pub fn calculate_stats(logs: &[LogEntry]) -> Vec<Guard> {
    let mut guards = HashMap::new();
    let mut guard: &mut Guard = &mut Guard::new(0);
    let mut fell_asleep = None;

    for log in logs {
        match log.event {
            Event::StartShift(id) => {
                guard = guards.entry(id).or_insert(Guard::new(id));
            }
            Event::FallAsleep => {
                fell_asleep = Some(log.time);
            }
            Event::WakeUp => {
                let start = fell_asleep.expect("Already awake");
                guard.register_sleep_time(start.minute, log.time.minute);
                fell_asleep = None;
            }
        }
    }
    let guard_vec: Vec<Guard> = guards.values().map(|v| *v).collect();
    guard_vec
}

pub fn part1(input: &[LogEntry]) -> u32 {
    let guards = calculate_stats(input);
    let max_guard = guards.iter().max_by_key(|g| g.minutes_asleep).unwrap();
    let max_freq = max_guard.frequency.iter().zip(0..).max().unwrap().1;
    max_guard.id * max_freq
}

pub fn part2(input: &[LogEntry]) -> u32 {
    let guards = calculate_stats(input);
    let (id, minute) = guards
        .iter()
        .map(|g| {
            let max_freq = g.frequency.iter().zip(0..).max().unwrap();
            (g.id, max_freq)
        })
        .max_by_key(|s| s.1)
        .unwrap();
    id * minute.1
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: &str = "[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up";

    #[test]
    fn test_import() {
        let logs = parse_data(DATA).unwrap();
        assert_eq!(
            logs,
            [
                LogEntry::new(Time::new(1518, 11, 1, 0, 0), Event::StartShift(10)),
                LogEntry::new(Time::new(1518, 11, 1, 0, 5), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 1, 0, 25), Event::WakeUp),
                LogEntry::new(Time::new(1518, 11, 1, 0, 30), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 1, 0, 55), Event::WakeUp),
                LogEntry::new(Time::new(1518, 11, 1, 23, 58), Event::StartShift(99)),
                LogEntry::new(Time::new(1518, 11, 2, 0, 40), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 2, 0, 50), Event::WakeUp),
                LogEntry::new(Time::new(1518, 11, 3, 0, 5), Event::StartShift(10)),
                LogEntry::new(Time::new(1518, 11, 3, 0, 24), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 3, 0, 29), Event::WakeUp),
                LogEntry::new(Time::new(1518, 11, 4, 0, 2), Event::StartShift(99)),
                LogEntry::new(Time::new(1518, 11, 4, 0, 36), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 4, 0, 46), Event::WakeUp),
                LogEntry::new(Time::new(1518, 11, 5, 0, 3), Event::StartShift(99)),
                LogEntry::new(Time::new(1518, 11, 5, 0, 45), Event::FallAsleep),
                LogEntry::new(Time::new(1518, 11, 5, 0, 55), Event::WakeUp),
            ]
        );
    }

    #[test]
    fn test_max_asleep() {
        let logs = parse_data(DATA).unwrap();
        let guards = calculate_stats(&logs);
        let max_guard = guards.iter().max_by_key(|g| g.minutes_asleep).unwrap();
        assert_eq!(max_guard.id, 10);
    }

    #[test]
    fn test_frequency() {
        let logs = parse_data(DATA).unwrap();
        let guards = calculate_stats(&logs);
        let max_guard = guards.iter().max_by_key(|g| g.minutes_asleep).unwrap();
        let max_freq = max_guard.frequency.iter().zip(0..).max().unwrap();
        println!("{:?}", max_guard.frequency);
        assert_eq!(max_freq.1, 24);
    }

    #[test]
    fn test_part1() {
        let logs = parse_data(DATA).unwrap();
        assert_eq!(part1(&logs), 240)
    }

    #[test]
    fn test_part2() {
        let logs = parse_data(DATA).unwrap();
        assert_eq!(part2(&logs), 4455)
    }
}
