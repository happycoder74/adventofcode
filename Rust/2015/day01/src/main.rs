use aoc_utils::{AocError, AocPartResult, AocResult, AocReturn};
use std::time::Instant;

trait Puzzle<T, U, V> {
    fn get_input(year: u32, day: u32) -> String;
    fn parse_input(input: &str) -> T;
    fn solve_part_1(&self, input: &T) -> Result<AocPartResult<U>, AocError>;
    fn solve_part_2(&self, input: &T) -> Result<AocPartResult<V>, AocError>;
    fn solve_all(&self) -> AocReturn<U, V>;
}

pub struct Day2015_01 {
    year: u32,
    day: u32,
}

impl Puzzle<Vec<i32>, i32, usize> for Day2015_01 {
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

    fn solve_part_1(&self, input: &Vec<i32>) -> Result<AocPartResult<i32>, AocError> {
        let start_time = Instant::now();
        let final_floor: i32 = input.iter().sum();
        let duration = Instant::now() - start_time;
        Ok(AocPartResult {
            result: aoc_utils::AocResult::new(final_floor),
            duration,
        })
    }

    fn solve_part_2(&self, input: &Vec<i32>) -> Result<AocPartResult<usize>, AocError> {
        let start_time = Instant::now();
        let mut level = 0;

        for (i, x) in input.iter().enumerate() {
            level += x;
            if level < 0 {
                let duration = Instant::now() - start_time;
                return Ok(AocPartResult {
                    result: AocResult::new(i + 1),
                    duration,
                });
            }
        }

        unreachable!()
    }
    fn solve_all(&self) -> AocReturn<i32, usize> {
        let input = Self::get_input(self.year, self.day);
        let input = Self::parse_input(&input);
        let return1 = self.solve_part_1(&input);
        let return2 = self.solve_part_2(&input);
        AocReturn::from_parts(return1, return2)
    }
}

fn main() {
    let day = Day2015_01 { year: 2015, day: 1 };

    let results = day.solve_all();

    aoc_utils::report::<i32, usize>(results);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1a() {
        let input = String::from("(())");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(0i32, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1b() {
        let input = String::from("()()");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(0, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1c() {
        let input = String::from("(((");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1d() {
        let input = String::from("(()(()(");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1e() {
        let input = String::from("))(((((");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1f() {
        let input = String::from("())");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-1, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1g() {
        let input = String::from("))(");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-1, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1h() {
        let input = String::from(")))");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_1i() {
        let input = String::from(")())())");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_1(&Day2015_01::parse_input(&input));
        assert_eq!(-3, result.unwrap().result.into());
    }

    #[test]
    fn test_part_2a() {
        let input = String::from(")");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_2(&Day2015_01::parse_input(&input));
        assert_eq!(1usize, result.unwrap().result.into());
    }

    #[test]
    fn test_part_2b() {
        let input = String::from("()())");
        let day = Day2015_01 { year: 2015, day: 1 };
        let result = day.solve_part_2(&Day2015_01::parse_input(&input));
        assert_eq!(5usize, result.unwrap().result.into());
    }
}
