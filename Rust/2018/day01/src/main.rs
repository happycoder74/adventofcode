use std::num::ParseIntError;

use aoc_utils::aoc_get_data;

fn parse_data(input: &str) -> Result<Vec<i32>, ParseIntError> {
    input
        .lines()
        .map(str::to_string)
        .map(|s| s.parse::<i32>())
        .collect()
}

fn part1(input: &[i32]) -> i32 {
    input.iter().sum()
}

fn part2(input: &[i32]) -> i32 {
    let mut frequencies = std::collections::HashSet::new();
    let mut frequency: i32 = 0;

    frequencies.insert(frequency);

    loop {
        for f in input {
            frequency += f;
            if frequencies.contains(&frequency) {
                return frequency;
            }
            frequencies.insert(frequency);
        }
    }
}

fn main() {
    let content = aoc_get_data!("2018", "01");
    if let Ok(parsed) = parse_data(content) {
        let start = std::time::Instant::now();
        println!("Part1: {:<20} [{:?}]", part1(&parsed), start.elapsed());
        let start = std::time::Instant::now();
        println!("Part2: {:<20} [{:?}]", part2(&parsed), start.elapsed());
    }
}
