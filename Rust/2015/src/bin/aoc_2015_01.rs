use std::time::{Instant, Duration};
use aoc_utils::AocReturn;

trait Puzzle<T, U> {
    fn get_input(year: u32, day: u32) -> String;
    fn parse_input(input: &str) -> T;
    fn solve_part_1(input: &T) -> U;
    fn solve_part_2(input: &T) -> U;
}

pub struct Day2015_01 {
    year: u32,
    day: u32
}

impl Puzzle<String, AocReturn> for Day2015_01 {
    fn get_input(year: u32, day: u32) -> String {
        return aoc_utils::get_input(year, day, false)
    }
    fn parse_input(input: &str) -> String {
        String::from(input)
    }

    fn solve_part_1(input: &String) -> AocReturn {
        let start_time = Instant::now();
        let final_floor = input
            .chars()
            .map(|x|
                match x {
                    '(' => 1,
                    ')' => -1,
                    _ => 0
                })
        .sum();
        let duration = Instant::now() - start_time;
        return AocReturn{result: final_floor, duration}
    }
    fn solve_part_2(input: &String) -> AocReturn {
        let start_time = Instant::now();
        let basement_found = false;
        let mut counter = 0;
        let mut level = 0;

        for ch in input.chars() {
            match ch {
                '(' => level += 1,
                ')' => level -= 1,
                _ => ()
            }
            if !basement_found {
                counter += 1;
                if level == -1 {
                    return AocReturn {result: counter, duration: Instant::now() - start_time}
                }
            }
        }

        return AocReturn {result: counter, duration: Duration::new(0, 0)};
    }
}

impl Day2015_01 {
    fn solve_all(self) -> (AocReturn, AocReturn) {
        let input = Day2015_01::get_input(self.year, self.day);
        let input = Day2015_01::parse_input(&input);
        let return1 = Day2015_01::solve_part_1(&input);
        let return2 = Day2015_01::solve_part_2(&input);
        return (return1, return2);
    }
}

fn main() {
    let day = Day2015_01 {year : 2015, day : 1};

    let results = day.solve_all();

    aoc_utils::report("Part 1", results.0);
    aoc_utils::report("Part 2", results.1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1a() {
        let input = String::from("(())");
        let result = Day2015_01::solve_part_1(&input);
        assert_eq!(0, result.result);
    }

    #[test]
    fn test_part_1b() {
        let input = String::from("()()");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(0, result.result);
    }

    #[test]
    fn test_part_1c() {
        let input = String::from("(((");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(3, result.result);

    }

    #[test]
    fn test_part_1d() {
        let input = String::from("(()(()(");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(3, result.result);
    }


    #[test]
    fn test_part_1e() {
        let input = String::from("))(((((");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(3, result.result);
    }


    #[test]
    fn test_part_1f() {
        let input = String::from("())");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(-1, result.result);
    }


    #[test]
    fn test_part_1g() {
        let input = String::from("))(");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(-1, result.result);
    }


    #[test]
    fn test_part_1h() {
        let input = String::from(")))");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(-3, result.result);
    }


    #[test]
    fn test_part_1i() {
        let input = String::from(")())())");
        let result = Day2015_01::solve_part_1(&String::from(input));
        assert_eq!(-3, result.result);
    }

    #[test]
    fn test_part_2a() {
        let input = String::from(")");
        let result = Day2015_01::solve_part_2(&String::from(input));
        assert_eq!(1, result.result);
    }

    #[test]
    fn test_part_2b() {
        let input = String::from("()())");
        let result = Day2015_01::solve_part_2(&String::from(input));
        assert_eq!(5, result.result);
    }

}
