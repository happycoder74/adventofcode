use aoc_utils::report;
use std::time::{Duration, Instant};

fn get_numbers(input: &str, digit_map: &[(&str, i32); 18]) -> (i32, i32) {
    let res_first: Vec<_> = digit_map
        .iter()
        .filter_map(|(k, v)| match input.find(*k) {
            Some(x) => Some((x, v)),
            _ => None,
        })
        .collect();

    let res_last: Vec<_> = digit_map
        .iter()
        .filter_map(|(k, v)| match input.rfind(*k) {
            Some(x) => Some((x, v)),
            _ => None,
        })
        .collect();
    (
        *res_first.iter().min_by_key(|x| x.0).unwrap().1,
        *res_last.iter().max_by_key(|x| x.0).unwrap().1,
    )
}

fn solve_part_1(input: &str) -> (i32, Duration) {
    let start_time = Instant::now();

    let result = input
        .lines()
        .map(|line| {
            let mut items = line.char_indices().filter_map(|(_, c)| c.to_digit(10));
            let first = items.next().unwrap();
            let last = items.next_back().unwrap_or(first);

            (first * 10) + last
        })
        .sum::<u32>() as i32;
    (result, Instant::now() - start_time)
}

fn solve_part_2(input: &str) -> (i32, Duration) {
    const MAP_P2: [(&str, i32); 18] = [
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ];
    let start_time = Instant::now();
    let result = input
        .lines()
        // .map(|line| get_numbers(line, &map_p2))
        .map(|line| get_numbers(line, &MAP_P2))
        .map(|(f, l)| f * 10 + l)
        .sum();
    (result, Instant::now() - start_time)
}

pub fn run(test_case: bool) {
    let input = aoc_utils::read_input(2023, 1, test_case);
    report("Part 1", solve_part_1(&input));
    report("Part 2", solve_part_2(&input));
}

#[cfg(test)]
mod tests {
    use super::*;
    const DIGIT_MAP: [(&str, i32); 18] = [
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ];

    #[test]
    fn test_get_numbers_first_and_last() {
        let line = "1abcde2";
        assert_eq!(get_numbers(line, &DIGIT_MAP), (1, 2));
    }

    #[test]
    fn test_get_numbers_first_and_last_with_all_digits() {
        let line = "612543029";
        assert_eq!(get_numbers(line, &DIGIT_MAP), (6, 9));
    }

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2023, 1, true);
        assert_eq!(142, solve_part_1(&input).0)
    }

    #[test]
    fn test_part_2() {
        let input = aoc_utils::read_input_alternative_file(2023, 1, "test_input_2.txt");
        assert_eq!(281, solve_part_2(&input).0)
    }
}
