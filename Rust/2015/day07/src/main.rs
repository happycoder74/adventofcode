use std::{
    collections::{HashMap, VecDeque},
    time::Instant,
};

use aoc_utils::{read_input, AocError, AocPartReturn, AocResult, AocReturn, Puzzle};

struct Instructions {
    operation: String,
    destination: String,
}

struct Day {
    input: String,
}

impl Day {
    fn new(year: u32, day: u32) -> Self {
        let input = read_input(year, day, false);
        Self { input }
    }

    fn solver(
        instructions: &VecDeque<Instructions>,
        return_key: &str,
        preset: Option<(&str, u32)>,
    ) -> u32 {
        let mut result = HashMap::<&str, u32>::new();
        if preset.is_some() {
            let (key, value) = preset.unwrap();
            result.insert(key, value);
        }

        let mut working_data = instructions.iter().clone().collect::<VecDeque<_>>();

        while !working_data.is_empty() {
            let instruction = working_data.pop_front().unwrap();
            if preset.is_some() && instruction.destination == preset.unwrap().0 {
                continue;
            } else {
                let mut expression = instruction.operation.split_whitespace();
                match expression.clone().count() {
                    1 => match instruction.operation.parse::<u32>() {
                        Ok(x) => _ = result.insert(&instruction.destination, x),
                        Err(_) => {
                            if result.contains_key(&instruction.operation.as_str()) {
                                result.insert(
                                    instruction.destination.as_str(),
                                    *result.get(instruction.operation.as_str()).unwrap(),
                                );
                            } else {
                                working_data.push_back(instruction);
                            }
                        }
                    },
                    2 => {
                        let op = expression.next().unwrap();
                        let right;
                        if op == "NOT" {
                            let rop = expression.next().unwrap();
                            match rop.parse::<u32>() {
                                Ok(x) => right = x,
                                Err(_) => {
                                    if result.contains_key(&rop) {
                                        right = *result.get(&rop).unwrap();
                                    } else {
                                        working_data.push_back(instruction);
                                        continue;
                                    }
                                }
                            }

                            result.insert(&instruction.destination, !right);
                        }
                    }
                    _ => {
                        let lop = expression.next().unwrap();
                        if !result.contains_key(&lop) && lop.parse::<u32>().is_err() {
                            working_data.push_back(instruction);
                            continue;
                        }
                        let op = expression.next().unwrap();
                        let rop = expression.next().unwrap();
                        if !result.contains_key(&rop) && rop.parse::<u32>().is_err() {
                            working_data.push_back(instruction);
                            continue;
                        }
                        let left = match lop.parse::<u32>() {
                            Ok(x) => x,
                            Err(_) => *result.get(&lop).unwrap_or_else(|| {
                                println!("Error in {lop}");
                                panic!();
                            }),
                        };
                        let right = match rop.parse::<u32>() {
                            Ok(x) => x,
                            Err(_) => *result.get(&rop).unwrap(),
                        };

                        match op {
                            "AND" => {
                                result.insert(&instruction.destination, left & right);
                            }
                            "OR" => {
                                result.insert(&instruction.destination, left | right);
                            }
                            "LSHIFT" => {
                                result.insert(&instruction.destination, left << right);
                            }
                            "RSHIFT" => {
                                result.insert(&instruction.destination, left >> right);
                            }
                            _ => (),
                        }
                    }
                }
            }
        }
        result[return_key]
    }
}

impl Puzzle<VecDeque<Instructions>> for Day {
    fn parse_input(input: &str) -> VecDeque<Instructions> {
        input
            .lines()
            .map(|line| {
                let (op, dest) = line.split_once(" -> ").unwrap();
                Instructions {
                    operation: op.to_string(),
                    destination: dest.to_string(),
                }
            })
            .collect()
    }

    fn solve_part_1(input: &VecDeque<Instructions>) -> Result<AocPartReturn, AocError> {
        let start_time = Instant::now();
        let result = Self::solver(input, "a", None);
        Ok(AocPartReturn {
            result: AocResult::U32(result),
            duration: Instant::now() - start_time,
        })
    }

    fn solve_part_2(input: &VecDeque<Instructions>) -> Result<AocPartReturn, AocError> {
        let start_time = Instant::now();
        let preset = ("b", Self::solve_part_1(input).unwrap().result.into());
        let result = Self::solver(input, "a", Some(preset));
        Ok(AocPartReturn {
            result: AocResult::U32(result),
            duration: Instant::now() - start_time,
        })
    }

    fn solve_all(self) -> AocReturn {
        let parsed_input = Self::parse_input(&self.input);
        let part1_result = Self::solve_part_1(&parsed_input);
        let part2_result = Self::solve_part_2(&parsed_input);
        AocReturn::from_parts(part1_result, part2_result)
    }
}

fn main() {
    let day = Day::new(2015, 7);

    let results = day.solve_all();

    aoc_utils::report(results);
}
