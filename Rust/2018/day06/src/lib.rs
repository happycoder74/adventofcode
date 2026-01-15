#![allow(dead_code, unused)]

use std::{num::ParseIntError, str::FromStr};

#[derive(Debug)]
pub enum AocError {
    EmptyRange,
}

#[derive(Debug)]
pub enum ParseError {
    ParseCoordError,
}

#[derive(Debug, Eq, PartialEq)]
pub struct Coord {
    x: u32,
    y: u32,
}

impl FromStr for Coord {
    type Err = ParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (x, y) = s.split_once(", ").ok_or(ParseError::ParseCoordError)?;
        Ok(Self {
            x: x.parse().map_err(|_| ParseError::ParseCoordError)?,
            y: y.parse().map_err(|_| ParseError::ParseCoordError)?,
        })
    }
}

impl Coord {
    fn new(x: u32, y: u32) -> Self {
        Coord { x, y }
    }

    fn distance(&self, x: u32, y: u32) -> u32 {
        self.x.abs_diff(x) + self.y.abs_diff(y)
    }
}

pub fn parse(input: &str) -> Result<Vec<Coord>, ParseError> {
    input.lines().map(str::parse).collect()
}

pub fn part1(coordinates: &[Coord]) -> Result<usize, AocError> {
    let mut sizes = vec![0usize; coordinates.len()];
    let mut infinite = vec![false; coordinates.len()];

    let max_x = coordinates
        .iter()
        .max_by_key(|c| c.x)
        .map(|c| c.x)
        .ok_or(AocError::EmptyRange)?;
    let max_y = coordinates
        .iter()
        .max_by_key(|c| c.y)
        .map(|c| c.y)
        .ok_or(AocError::EmptyRange)?;

    for y in 0..=max_y {
        for x in 0..=max_x {
            let distances = coordinates
                .iter()
                .map(|c| c.distance(x, y))
                .enumerate()
                .collect::<Vec<_>>();
            let (min_index, minimum) = distances
                .iter()
                .min_by_key(|p| p.1)
                .ok_or(AocError::EmptyRange)?;
            let count = distances.iter().filter(|p| p.1 == *minimum).count();
            if count == 1 {
                if x == 0 || x == max_x || y == 0 || y == max_y {
                    infinite[*min_index] = true;
                }
                sizes[*min_index] += 1;
            }
        }
    }

    let result = sizes
        .iter()
        .zip(infinite)
        .filter(|(_, inf)| (!inf))
        .map(|(s, _)| s)
        .max()
        .ok_or(AocError::EmptyRange)?;

    Ok(*result)
}
pub fn part2(coordinates: &[Coord], safe_distance: u32) -> Result<usize, AocError> {
    let mut count = 0usize;
    let max_x = coordinates
        .iter()
        .max_by_key(|c| c.x)
        .map(|c| c.x)
        .ok_or(AocError::EmptyRange)?;
    let max_y = coordinates
        .iter()
        .max_by_key(|c| c.y)
        .map(|c| c.y)
        .ok_or(AocError::EmptyRange)?;

    for y in 0..=max_y {
        for x in 0..=max_x {
            let distance: u32 = coordinates.iter().map(|c| c.distance(x, y)).sum();

            if distance < safe_distance {
                count += 1;
            }
        }
    }

    Ok(count)
}

#[cfg(test)]
mod tests {
    use super::{Coord, parse, part1, part2};

    const DATA: &str = "1, 1
1, 6
8, 3
3, 4
5, 5
8, 9";

    #[test]
    fn test_parse() {
        let result = parse(DATA).unwrap();
        let expected: Vec<Coord> = vec![
            Coord::new(1, 1),
            Coord::new(1, 6),
            Coord::new(8, 3),
            Coord::new(3, 4),
            Coord::new(5, 5),
            Coord::new(8, 9),
        ];
        assert_eq!(result, expected);
    }

    #[test]
    fn test_part_1() {
        let input = parse(DATA).unwrap();
        let result = part1(&input).unwrap();
        assert_eq!(17, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse(DATA).unwrap();
        let result = part2(&input, 32).unwrap();
        assert_eq!(16, result);
    }
}
