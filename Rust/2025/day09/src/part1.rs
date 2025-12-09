#![allow(unused_variables)]
use aoc_utils::NotImplementedError;
use itertools::Itertools;
use std::num::ParseIntError;

#[derive(Debug, Eq, Hash, PartialEq)]
struct Location {
    x: usize,
    y: usize,
}

impl std::str::FromStr for Location {
    type Err = ParseIntError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut loc = s.split(',');
        let x: usize = loc.next().unwrap().parse()?;
        let y: usize = loc.next().unwrap().parse()?;

        Ok(Self { x, y })
    }
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let parsed = input
        .lines()
        .map(|line| line.trim().parse::<Location>().unwrap())
        .collect::<Vec<_>>();

    let combos = parsed
        .iter()
        .combinations(2)
        .map(|v| {
            let l1 = v[0];
            let l2 = v[1];
            let area = (l1.x.abs_diff(l2.x) + 1) * (l1.y.abs_diff(l2.y) + 1);
            area
        })
        .max()
        .unwrap();

    Ok(combos)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3";

        assert_eq!(super::solve_part(input).unwrap(), 50);
    }
}
