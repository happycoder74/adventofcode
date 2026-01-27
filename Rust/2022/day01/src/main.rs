use std::fmt::Display;

use aoc_utils::aoc_get_data;

#[derive(Debug)]
struct NumberError;

impl Display for NumberError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "NumberError")
    }
}

fn solve_part_1(input: &Vec<Vec<u32>>) -> Result<u32, NumberError> {
    Ok(input
        .iter()
        .map(|v| v.iter().sum())
        .max()
        .ok_or(NumberError)?)
}

fn solve_part_2(input: &Vec<Vec<u32>>) -> Result<u32, String> {
    let mut packages: Vec<_> = input.iter().map(|v| v.iter().sum()).collect();

    packages.sort_unstable();

    Ok(packages.iter().rev().take(3).sum())
}

fn parse_input(input: &str) -> Vec<Vec<u32>> {
    input
        .trim()
        .split("\n\n")
        .map(|s| {
            s.split_ascii_whitespace()
                .map(|s| s.parse::<u32>().unwrap())
                .collect()
        })
        .collect()
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "01");
    let commands = parse_input(&input);

    let start = std::time::Instant::now();
    match solve_part_1(&commands) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&commands) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: &str = "1000
2000
3000

4000

5000
6000

7000
8000
9000

10000";

    #[test]
    fn test_grouping() {
        let result = parse_input(DATA);
        assert_eq!(
            vec![
                vec![1000, 2000, 3000],
                vec![4000],
                vec![5000, 6000],
                vec![7000, 8000, 9000],
                vec![10000]
            ],
            result
        );
    }

    #[test]
    fn test_part_1() {
        let input = parse_input(DATA);
        let result = solve_part_1(&input).unwrap();
        assert_eq!(24_000, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA);
        let result = solve_part_2(&input).unwrap();
        assert_eq!(45_000, result);
    }
}
