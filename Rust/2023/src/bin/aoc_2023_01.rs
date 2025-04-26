use aoc_utils::output::report;
use std::collections::HashMap;
use std::time::{Duration, Instant};

fn get_numbers(input: &str, digit_map: &HashMap<&str, i32>) -> (i32, i32) {
    let res_first: Vec<_> = digit_map
        .iter()
        .filter(|(k, _)| (input.find(*k).is_some()))
        .map(|(k, v)| (input.find(k).unwrap(), v))
        .collect();

    let res_last: Vec<_> = digit_map
        .iter()
        .filter(|(k, _)| (input.rfind(*k).is_some()))
        .map(|(k, v)| (input.rfind(k).unwrap(), v))
        .collect();

    (
        *res_first.iter().min_by_key(|x| x.0).unwrap().1,
        *res_last.iter().max_by_key(|x| x.0).unwrap().1,
    )
}

fn solve_part_1(input: &str) -> (i32, Duration) {
    let start_time = Instant::now();
    let map = HashMap::from_iter([
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
    ]);
    let result = input
        .lines()
        .map(|line| get_numbers(line, &map))
        .map(|(f, l)| f * 10 + l)
        .sum();
    (result, Instant::now() - start_time)
}

fn solve_part_2(input: &str) -> (i32, Duration) {
    let map_p2: HashMap<&str, i32> = HashMap::from_iter([
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
    ]);
    let start_time = Instant::now();
    let result = input
        .lines()
        .map(|line| get_numbers(line, &map_p2))
        .map(|(f, l)| f * 10 + l)
        .sum();
    (result, Instant::now() - start_time)
}

pub fn main() {
    let input = aoc_utils::read_input(2023, 1, false);
    report("Part 1", solve_part_1(&input));
    report("Part 2", solve_part_2(&input));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2023, 4, true);
        assert_eq!(142, solve_part_1(&input).0)
    }
}
