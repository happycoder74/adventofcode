use std::time::Instant;
use std::collections::HashSet;
use aoc_utils::input::get_input;
use aoc_utils::types::AocReturn;
use aoc_utils::output::report;

type Cards = HashSet<i32>;

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

fn solve_part_1(input: &[(Cards, Cards)]) -> AocReturn {
    let start_time = Instant::now();
    let result: i32 = input
        .iter()
        .map(|(winning, hand)| winning.intersection(hand).count())
        .map(|n| match n {
            0 => 0,
            n => 1 << (n - 1),
        })
        .sum();
    AocReturn {result, duration: Instant::now() - start_time}
}

fn solve_part_2(input: &[(Cards, Cards)]) -> AocReturn {
    let start_time = Instant::now();
    let result = input.len() as i32;
    AocReturn {result, duration: Instant::now() - start_time}
}

pub fn main() {
    let input = get_input(2023, 4);
    let data = parse_input(&input);
    report("Part 1", solve_part_1(&data));
    report("Part 2", solve_part_2(&data));
}
