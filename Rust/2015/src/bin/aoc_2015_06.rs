use aoc_utils::types::Puzzle;
use std::time::{Duration, Instant};

pub struct Day2015_06 {
    year: u32,
    day: u32,
}

#[derive(PartialEq, Debug)]
enum Mode {
    Toggle,
    On,
    Off,
    Undefined,
}

#[derive(Debug, PartialEq, Eq, Hash)]
struct Point {
    x: u32,
    y: u32,
}

impl Point {
    pub fn new(x: u32, y: u32) -> Self {
        Self { x, y }
    }
}

#[derive(Debug)]
struct Action {
    mode: Mode,
    region_start: Point,
    region_end: Point,
}

impl Action {
    fn new() -> Self {
        Self {
            mode: Mode::Undefined,
            region_start: Point::new(0, 0),
            region_end: Point::new(0, 0),
        }
    }
}

impl Puzzle<Vec<Action>, (u32, Duration)> for Day2015_06 {
    fn parse_input(input: &str) -> Vec<Action> {
        let mut return_data: Vec<Action> = vec![];
        for line in input.split('\n') {
            let mut action = Action::new();
            let line_to_parse = line.replace("turn o", "turn_o");
            let mut parse_line = line_to_parse.split_whitespace();
            match parse_line.next() {
                Some(x) => match x {
                    "toggle" => action.mode = Mode::Toggle,
                    "turn_on" => action.mode = Mode::On,
                    "turn_off" => action.mode = Mode::Off,
                    _ => panic!("Should not be here"),
                },
                _ => continue,
            }
            let start: Vec<_> = parse_line.next().unwrap().split(',').collect();
            let end: Vec<_> = parse_line.skip(1).next().unwrap().split(',').collect();
            action.region_start = Point::new(start[0].parse().unwrap(), start[1].parse().unwrap());
            action.region_end = Point::new(end[0].parse().unwrap(), end[1].parse().unwrap());

            return_data.push(action);
        }
        return_data
    }

    fn solve_part_1(instructions: &Vec<Action>) -> (u32, Duration) {
        const DIMENSION: usize = 1000;
        let start_time = Instant::now();
        let mut grid: [[bool; DIMENSION]; DIMENSION] = [[false; DIMENSION]; DIMENSION];
        for action in instructions {
            for ix in action.region_start.x..=action.region_end.x {
                for iy in action.region_start.y..=action.region_end.y {
                    let (x, y): (usize, usize) = (ix as usize, iy as usize);
                    match action.mode {
                        Mode::Toggle => {
                            grid[y][x] ^= true;
                        }
                        Mode::Off => {
                            grid[y][x] = false;
                        }
                        Mode::On => {
                            grid[y][x] = true;
                        }
                        _ => continue,
                    }
                }
            }
        }
        let result: usize = grid
            .iter()
            .map(|row| row.iter().filter(|&&col| col).count())
            .sum();
        (result as u32, Instant::now() - start_time)
    }

    fn solve_part_2(_instructions: &Vec<Action>) -> (u32, Duration) {
        let start_time = Instant::now();
        let result = 0;
        (result as u32, Instant::now() - start_time)
    }
    fn solve_all(self) -> ((u32, Duration), (u32, Duration)) {
        let input = Day2015_06::get_input(self.year, self.day, false);
        let input = Day2015_06::parse_input(&input);
        let return1 = Day2015_06::solve_part_1(&input);
        let return2 = Day2015_06::solve_part_2(&input);
        (return1, return2)
    }
}

fn main() {
    let day = Day2015_06 { year: 2015, day: 6 };

    let results = day.solve_all();

    aoc_utils::report("Part 1", results.0);
    aoc_utils::report("Part 2", results.1);
}

// #[cfg(test)]
// mod tests {
//     use super::*;

// }
