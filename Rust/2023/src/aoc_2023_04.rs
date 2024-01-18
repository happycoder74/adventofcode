use std::collections::HashSet;

type Cards = HashSet<i32>;
fn parse_cards(input: &str) -> Cards {
    input
        .split_whitespace()
        .map(|x| x.trim().parse().unwrap())
        .collect()
}

#[aoc_generator(day4)]
pub fn parse_input(input: &str) -> Vec<(Cards, Cards)> {
    let mut numbers = vec![];

    for line in input.lines() {
        let (_, line) = line.split_once(":").unwrap();
        let (winning, hand) = line.trim().split_once("|").unwrap();

        numbers.push((parse_cards(winning.trim()), parse_cards(hand.trim())));
    }

    numbers
}

#[aoc(day4, part1)]
pub fn solve_part_1(input: &[(Cards, Cards)]) -> i32 {
    input
        .iter()
        .map(|(winning, hand)| winning.intersection(hand).count())
        .map(|n| match n {
            0 => 0,
            n => 1 << (n - 1),
        })
        .sum()
}
