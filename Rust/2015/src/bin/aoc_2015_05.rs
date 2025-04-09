use aoc_utils::types::Puzzle;
use fancy_regex::Regex;
use std::time::{Duration, Instant};

pub struct Day2015_05 {
    year: u32,
    day: u32,
}

fn check_regex(line: &str, re: &Regex) -> bool {
    return match re.find(line).unwrap() {
        Some(_) => true,
        _ => false,
    };
}
impl Puzzle<String, (u32, Duration)> for Day2015_05 {
    fn parse_input(input: &str) -> String {
        String::from(input)
    }

    fn solve_part_1(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();
        let re_wovel = Regex::new(r"[aeiou].*[aeiou].*[aeiou]").unwrap();
        let re_double_letter = fancy_regex::Regex::new("(.)\\1").unwrap();
        let re_invalid = Regex::new(r"(ab|cd|pq|xy)").unwrap();

        let result = instructions
            .lines()
            .filter(|line| {
                return check_regex(line, &re_wovel)
                    && check_regex(line, &re_double_letter)
                    && !check_regex(line, &re_invalid);
            })
            .count();

        (result as u32, Instant::now() - start_time)
    }

    fn solve_part_2(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();
        let re_pairs = Regex::new(r"(..).*\1").unwrap();
        let re_repeat = Regex::new(r"(.).\1").unwrap();
        let result = instructions
            .lines()
            .filter(|line| {
                return check_regex(line, &re_pairs) && check_regex(line, &re_repeat);
            })
            .count();

        (result as u32, Instant::now() - start_time)
    }
    fn solve_all(self) -> ((u32, Duration), (u32, Duration)) {
        let input = Day2015_05::get_inputs(self.year, self.day, false);
        let input = Day2015_05::parse_input(&input);
        let return1 = Day2015_05::solve_part_1(&input);
        let return2 = Day2015_05::solve_part_2(&input);
        return (return1, return2);
    }
}

fn main() {
    let day = Day2015_05 { year: 2015, day: 5 };

    let results = day.solve_all();

    aoc_utils::report("Part 1", results.0);
    aoc_utils::report("Part 2", results.1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_check_wovel() {
        let re_wovel = Regex::new(r"[aeiou].*[aeiou].*[aeiou]").unwrap();
        let input = "aeiouaeiouaeiou";
        assert!(check_regex(input, &re_wovel));
    }

    #[test]
    fn test_check_wovel_false() {
        let re_wovel = Regex::new(r"[aeiou].*[aeiou].*[aeiou]").unwrap();
        let input = "dvszwmarrgswjxmb";
        assert_eq!(check_regex(input, &re_wovel), false);
    }

    #[test]
    fn test_check_double_letter() {
        let re_double_letter = Regex::new("(.)\\1").unwrap();
        let input = "aabbccdd";
        assert!(check_regex(input, &re_double_letter));
    }

    #[test]
    fn test_check_double_letter_false() {
        let re_double_letter = Regex::new("(.)\\1").unwrap();
        let input = "abcabcabc";
        assert!(!check_regex(input, &re_double_letter));
    }

    #[test]
    fn test_check_invalid() {
        let re_invalid = Regex::new(r"(ab|cd|pq|xy)").unwrap();
        let input = "ugknbfddgicrmopn";
        assert!(check_regex(input, &re_invalid) == false);
    }

    #[test]
    fn test_check_invalid_false() {
        let re_invalid = Regex::new(r"(ab|cd|pq|xy)").unwrap();
        let input = "abhgdi";
        assert!(check_regex(input, &re_invalid) == true);
    }
}
