use std::{error::Error, fmt::Display};

use anyhow::Result;
use aoc_utils::aoc_get_bytes;

#[allow(unused)]
#[derive(Debug, Eq, PartialEq)]
enum PartError {
    NotImplemented,
    Unreachable,
    SyntaxError,
}

impl Error for PartError {}

impl Display for PartError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Error - {}",
            match self {
                Self::NotImplemented => "Not implemented",
                Self::Unreachable => "Unreachable code",
                Self::SyntaxError => "Syntax Error",
            }
        )
    }
}

fn part1(input: &[u8]) -> Result<u32> {
    let mut root = md5::Context::new();
    root.consume(input.trim_ascii());

    for val in 0.. {
        let mut ctx = root.clone();
        ctx.consume(format!("{val}"));
        let res = ctx.finalize();
        if matches!(res.0, [0, 0, b, ..] if b >> 4 == 0) {
            return Ok(val);
        }
    }
    Err(PartError::SyntaxError.into())
}

fn part2(input: &[u8]) -> Result<u32> {
    let mut root = md5::Context::new();
    root.consume(input.trim_ascii());

    for val in 0.. {
        let mut ctx = root.clone();
        ctx.consume(format!("{val}"));
        let res = ctx.finalize();
        if matches!(res.0, [0, 0, 0, ..]) {
            return Ok(val);
        }
    }
    Err(PartError::SyntaxError.into())
}

fn main() {
    let data = aoc_get_bytes!("2015", "04");

    let start = std::time::Instant::now();
    if let Ok(part1_result) = part1(data) {
        println!("Part 1: {:<20} [{:?}]", part1_result, start.elapsed());
    }

    let start = std::time::Instant::now();
    if let Ok(part2_result) = part2(data) {
        println!("Part 1: {:<20} [{:?}]", part2_result, start.elapsed());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1_abcdef() {
        assert_eq!(609043, part1(b"abcdef").unwrap())
    }

    #[test]
    fn test_part_1_pqrstuv() {
        assert_eq!(1048970, part1(b"pqrstuv").unwrap())
    }
}
