use std::{fmt::Display, str::FromStr};

use aoc_utils::aoc_get_data;

#[derive(Debug)]
enum Player {
    Rock(u8),
    Paper(u8),
    Scissors(u8),
}

#[derive(Debug)]
struct GameError;

impl FromStr for Player {
    type Err = GameError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "A" | "X" => Ok(Self::Rock(1)),
            "B" | "Y" => Ok(Self::Paper(2)),
            "C" | "Z" => Ok(Self::Scissors(3)),
            _ => Err(GameError),
        }
    }
}

fn play(p1: &Player, p2: &Player) -> u32 {
    let result = u32::from(match p1 {
        Player::Rock(f) => match p2 {
            Player::Rock(s) => *s + 3,
            Player::Paper(s) => *s + 6,
            Player::Scissors(s) => *s,
        },
        Player::Paper(f) => match p2 {
            Player::Rock(s) => *s,
            Player::Paper(s) => *s + 3,
            Player::Scissors(s) => s + 6,
        },
        Player::Scissors(f) => match p2 {
            Player::Rock(s) => *s + 6,
            Player::Paper(s) => *s,
            Player::Scissors(s) => *s + 3,
        },
    });

    result
}

fn parse_input(input: &str) -> Result<Vec<(Player, Player)>, GameError> {
    let players = input
        .trim()
        .lines()
        .map(|s| {
            s.split_ascii_whitespace()
                .map(|p| p.parse::<Player>().unwrap())
        })
        .map(|mut p| (p.next().unwrap(), p.next().unwrap()))
        .collect::<Vec<_>>();

    Ok(players)
}

fn solve_part_1(input: &Vec<(Player, Player)>) -> Result<u32, String> {
    let result = input.iter().map(|(p1, p2)| play(p1, p2)).sum();
    Ok(result)
}

fn solve_part_2(input: &Vec<(Player, Player)>) -> Result<u32, String> {
    Err("Not implemented".to_string())
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "02");
    let input = parse_input(input).unwrap();

    let start = std::time::Instant::now();
    match solve_part_1(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&input) {
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

    const DATA: &str = "A Y
B X
C Z";

    #[test]
    fn test_part_1() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_1(&input).unwrap();
        assert_eq!(15, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!(45_000, result);
    }
}
