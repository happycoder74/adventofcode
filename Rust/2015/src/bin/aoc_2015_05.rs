use aoc_utils::types::Puzzle;
use std::time::{Duration, Instant};

pub struct Day2015_05 {
    year: u32,
    day: u32,
}

fn check_double_letter(line: &str) -> bool {
    let mut zipped = line.chars().zip(line.chars().skip(1));
    let result = zipped.any(|(a, b)| {
        return a == b;
    });

    result
}
fn check_no_invalid(line: &str) -> bool {
    let invalid = ["ab", "cd", "pq", "xy"];
    let result = invalid.iter().any(|s| match line.find(s) {
        Some(_) => true,
        _ => false,
    });

    return !result;
}

fn check_wovels(line: &str) -> bool {
    line.chars()
        .filter(|c| {
            for cc in "aeuio".chars() {
                if *c == cc {
                    return true;
                }
            }
            return false;
        })
        .count()
        >= 3
}

fn check_pairs(input: &str) -> bool {
    let zipped: Vec<_> = input.chars().zip(input.chars().skip(1)).collect();
    for p in zipped.iter().rev().skip(2).rev().enumerate() {
        let (i, pair) = p;
        match zipped.iter().rposition(|item| item == pair) {
            Some(x) => {
                if x > i + 1 {
                    return true;
                }
            }
            _ => {}
        }
    }
    false
}

fn check_repeat(input: &str) -> bool {
    let zipped: Vec<_> = input.chars().zip(input.chars().skip(2)).collect();
    for (a, b) in zipped {
        if a == b {
            return true;
        }
    }
    false
}

impl Puzzle<String, (u32, Duration)> for Day2015_05 {
    fn parse_input(input: &str) -> String {
        String::from(input)
    }

    fn solve_part_1(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();

        let result = instructions
            .lines()
            .filter(|line| {
                return check_wovels(line) && check_double_letter(line) && check_no_invalid(line);
            })
            .count();

        (result as u32, Instant::now() - start_time)
    }

    fn solve_part_2(instructions: &String) -> (u32, Duration) {
        let start_time = Instant::now();
        let result = instructions
            .lines()
            .filter(|line| {
                return check_pairs(line) && check_repeat(line);
            })
            .count();

        (result as u32, Instant::now() - start_time)
    }
    fn solve_all(self) -> ((u32, Duration), (u32, Duration)) {
        let input = Day2015_05::get_input(self.year, self.day, false);
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
        let input = "ugknbfddgicrmopn";
        assert!(check_no_invalid(input) == true);
    }

    #[test]
    fn test_check_invalid_false() {
        let input = "abhgdi";
        assert!(check_no_invalid(input) == false);
    }

    #[test]
    fn test_check_pairs_xyxy() {
        let input = "xyxy";
        let re_pairs = Regex::new(r"(..).*\1").unwrap();
        assert!(check_regex(input, &re_pairs));
    }

    #[test]
    fn test_check_pairs_aabcdefgaa() {
        let input = "aabcdefgaa";
        assert!(check_pairs(input));
    }

    #[test]
    fn test_check_pairs_aaa_fail() {
        let input = "aaa";
        assert_eq!(check_pairs(input), false);
    }

    #[test]
    fn test_check_double_letter_noregex() {
        let input = "abcdde";
        assert!(check_double_letter(input));
    }

    #[test]
    fn test_check_double_letter_noregex_fail() {
        let input = "jchzalrnumimnmhp";
        assert_eq!(check_double_letter(input), false);
    }

    #[test]
    fn test_check_repeat_good() {
        let good_input_repeat = vec!["xyx", "aaa", "abcdefeghi", "ieodomkazucvgmuy"];
        for line in good_input_repeat {
            assert!(check_repeat(line));
        }
    }

    #[test]
    fn test_check_repeat_bad() {
        let bad_input_repeat = vec!["uurcxstgmygtbstg"];
        for line in bad_input_repeat {
            assert_eq!(check_repeat(line), false);
        }
    }
}
