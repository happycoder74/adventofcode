use std::collections::HashSet;
use std::time::{Duration, Instant};
use aoc_utils::types::Puzzle;

struct Agent {
    x: i32,
    y: i32,
    coords: HashSet<(i32, i32)>
}

impl Agent {
    fn new() -> Self {
        Self {
            x: 0,
            y: 0,
            coords: HashSet::from([(0, 0)])
        }
    }

    fn make_step(&mut self, direction: &str) {
        match direction {
            "^" => self.y += 1,
            ">" => self.x += 1,
            "v" => self.y -=  1,
            "<" => self.x -=  1,
            _ => ()
        }
        self.coords.insert(self.location());
    }

    fn location(&self) -> (i32, i32) {
        (self.y, self.x)
    }

    fn get_locations(&self) -> usize {
        self.coords.len()
    }
}

pub struct Day2015_03 {
    year: u32,
    day: u32
}

impl Puzzle<String, (u32, Duration)> for Day2015_03 {
    fn get_input(year: u32, day: u32, testcase: bool) -> String {
        return aoc_utils::input::get_input(year, day, testcase)
    }
    fn parse_input(input: &str) -> String {
        String::from(input)
    }

    fn solve_part_1(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();
        let mut santa: Agent = Agent::new();

        for c in instructions.split("") {
            santa.make_step(&c);
        }

        (santa.get_locations() as u32, Instant::now() - start_time)
    }

    fn solve_part_2(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();
        let mut santa: Agent = Agent::new();
        let mut robosanta: Agent = Agent::new();

        let inst: Vec<&str> = instructions
            .split("")
            .filter(|s| !s.is_empty())
            .collect();

        let _: Vec<_> = inst
            .chunks(2)
            .map(|c| {
                match c {
                    [santa_step, robosanta_step] => {
                        santa.make_step(santa_step);
                        robosanta.make_step(robosanta_step);
                    },
                    _ => panic!("Invalid input")
                }
            })
            .collect();

        for location in robosanta.coords.iter() {
            santa.coords.insert(*location);
        }

        (santa.get_locations() as u32, Instant::now() - start_time)
    }
    fn solve_all(self) -> ((u32, Duration), (u32, Duration)) {
        let input = Day2015_03::get_input(self.year, self.day, false);
        let input = Day2015_03::parse_input(&input);
        let return1 = Day2015_03::solve_part_1(&input);
        let return2 = Day2015_03::solve_part_2(&input);
        return (return1, return2);
    }
}

fn main() {
    let day = Day2015_03 {year : 2015, day : 3};

    let results = day.solve_all();

    aoc_utils::report("Part 1", results.0);
    aoc_utils::report("Part 2", results.1);
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_agent_start() {
        let santa = Agent::new();
        assert_eq!((0, 0), santa.location());
    }

    #[test]
    fn test_agent_start_length() {
        let santa = Agent::new();
        assert_eq!(1, santa.get_locations());
    }

    #[test]
    fn test_agent_length_after_move() {
        let mut santa = Agent::new();
        santa.make_step(">");
        assert_eq!(2, santa.get_locations());
    }

    #[test]
    fn test_move_agent_up() {
        let mut santa = Agent::new();
        santa.make_step("^");
        assert_eq!((1, 0), santa.location());
    }

    #[test]
    fn test_move_agent_down() {
        let mut santa = Agent::new();
        santa.make_step("v");
        assert_eq!((-1, 0), santa.location());
    }

    #[test]
    fn test_move_agent_right() {
        let mut santa = Agent::new();
        santa.make_step(">");
        assert_eq!((0, 1), santa.location());
    }

    #[test]
    fn test_move_agent_left() {
        let mut santa = Agent::new();
        santa.make_step("<");
        assert_eq!((0, -1), santa.location());
    }

    #[test]
    fn test_part_1a() {
        let input = String::from(">");
        assert_eq!(2, Day2015_03::solve_part_1(&input).0);
    }

    #[test]
    fn test_part_1b() {
        let input = String::from("^>v<");
        assert_eq!(4, Day2015_03::solve_part_1(&input).0);
    }

    #[test]
    fn test_part_1c() {
        let input = String::from("^v^v^v^v^v");
        assert_eq!(2, Day2015_03::solve_part_1(&input).0);
    }

    #[test]
    fn test_part_2a() {
        let input = String::from("^v");
        assert_eq!(3, Day2015_03::solve_part_2(&input).0);
    }

    #[test]
    fn test_part_2b() {
        let input = String::from("^>v<");
        assert_eq!(3, Day2015_03::solve_part_2(&input).0);
    }

    #[test]
    fn test_part_2c() {
        let input = String::from("^v^v^v^v^v");
        assert_eq!(11, Day2015_03::solve_part_2(&input).0);
    }
}
