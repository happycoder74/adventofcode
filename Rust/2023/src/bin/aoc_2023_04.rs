use aoc_utils::report;
use aoc_utils::{AocError, AocPartReturn, AocResult, AocReturn};
use std::collections::HashSet;
use std::time::Instant;

type Cards = HashSet<u32>;

fn parse_cards(input: &str) -> Cards {
    input
        .split_whitespace()
        .map(|x| x.trim().parse().unwrap())
        .collect()
}

pub fn parse_input(input: &str) -> Vec<(Cards, Cards)> {
    let mut numbers = vec![];

    for line in input.lines() {
        let (_, line) = line.split_once(":").unwrap();
        let (winning, hand) = line.trim().split_once("|").unwrap();

        numbers.push((parse_cards(winning.trim()), parse_cards(hand.trim())));
    }

    numbers
}

fn solve_part_1(input: &[(Cards, Cards)]) -> Result<AocPartReturn, AocError> {
    let start_time = Instant::now();
    let result = input
        .iter()
        .map(|(winning, hand)| winning.intersection(hand).count())
        .map(|n| match n {
            0 => 0,
            n => 1 << (n - 1),
        })
        .sum();
    Ok(AocPartReturn {
        result: AocResult::U32(result),
        duration: Instant::now() - start_time,
    })
}

fn solve_part_2(_input: &[(Cards, Cards)]) -> Result<AocPartReturn, AocError> {
    Err(AocError::new("Not yet implemented"))
}

pub fn main() {
    let input = aoc_utils::read_input(2023, 4, false);
    let data = parse_input(&input);
    let part1 = solve_part_1(&data);
    let part2 = solve_part_2(&data);
    report(AocReturn::from_parts(part1, part2));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2023, 4, true);
        let cards = parse_input(&input);
        assert_eq!(13u32, solve_part_1(&cards).unwrap().result.into())
    }
}
