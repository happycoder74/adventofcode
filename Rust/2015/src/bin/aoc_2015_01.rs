use aoc_utils::{AocError, AocPartReturn, AocResult, AocReturn};
use std::time::Instant;

trait Puzzle<T> {
    fn get_input(year: u32, day: u32) -> String;
    fn parse_input(input: &str) -> T;
    fn solve_part_1(input: &T) -> Result<AocPartReturn, AocError>;
    fn solve_part_2(input: &T) -> Result<AocPartReturn, AocError>;
}

pub struct Day2015_01 {
    year: u32,
    day: u32,
}

impl Puzzle<Vec<i32>> for Day2015_01 {
    fn get_input(year: u32, day: u32) -> String {
        aoc_utils::read_input(year, day, false)
    }
    fn parse_input(input: &str) -> Vec<i32> {
        fn helper(b: u8) -> i32 {
            match b {
                b'(' => 1,
                b')' => -1,
                _ => 0,
            }
        }
        input.bytes().map(helper).collect()
    }

    fn solve_part_1(input: &Vec<i32>) -> Result<AocPartReturn, AocError> {
        let start_time = Instant::now();
        let final_floor: i32 = input.iter().sum();
        let duration = Instant::now() - start_time;
        Ok(AocPartReturn {
            result: aoc_utils::AocResult::I32(final_floor),
            duration,
        })
    }

    fn solve_part_2(input: &Vec<i32>) -> Result<AocPartReturn, AocError> {
        let start_time = Instant::now();
        let mut level = 0;

        for (i, x) in input.iter().enumerate() {
            level += x;
            if level < 0 {
                let duration = Instant::now() - start_time;
                return Ok(AocPartReturn {
                    result: AocResult::Usize(i + 1),
                    duration,
                });
            }
        }

        unreachable!()
    }
}

impl Day2015_01 {
    fn solve_all(self) -> AocReturn {
        let input = Self::get_input(self.year, self.day);
        let input = Self::parse_input(&input);
        let return1 = Self::solve_part_1(&input);
        let return2 = Self::solve_part_2(&input);
        AocReturn::from_parts(return1, return2)
    }
}

fn main() {
    let day = Day2015_01 { year: 2015, day: 1 };

    let results = day.solve_all();

    aoc_utils::report(results);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1a() {
        let input = String::from("(())");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(0, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1b() {
        let input = String::from("()()");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(0, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1c() {
        let input = String::from("(((");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1d() {
        let input = String::from("(()(()(");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1e() {
        let input = String::from("))(((((");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1f() {
        let input = String::from("())");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-1, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1g() {
        let input = String::from("))(");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-1, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1h() {
        let input = String::from(")))");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1i() {
        let input = String::from(")())())");
        let result = Day2015_01::solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_2a() {
        let input = String::from(")");
        let result = Day2015_01::solve_part_2(&Day2015_01::parse_input(&input));
        assert_eq!(1, result.unwrap().result.into());
    }

    #[test]
    fn test_part_2b() {
        let input = String::from("()())");
        let result = Day2015_01::solve_part_2(&Day2015_01::parse_input(&input));
        assert_eq!(5, result.unwrap().result.into());
    }
}
