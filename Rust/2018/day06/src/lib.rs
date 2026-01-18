#![allow(dead_code, unused)]

use itertools::Itertools;
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

#[derive(Eq, PartialEq, Debug)]
pub struct GridSize {
    x: u32,
    y: u32,
}

impl GridSize {
    fn new(x: u32, y: u32) -> Self {
        Self { x, y }
    }
}

pub fn parse(input: &str) -> Result<Vec<Coord>, ParseError> {
    input.lines().map(str::parse).collect()
}

pub fn calc_grid_size(coordinates: &[Coord]) -> Result<GridSize, AocError> {
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

    Ok(GridSize { x: max_x, y: max_y })
}

pub fn part1(coordinates: &[Coord], grid_size: &GridSize) -> Result<usize, AocError> {
    let mut sizes = vec![0usize; coordinates.len()];
    let mut infinite = vec![false; coordinates.len()];

    for (y, x) in (0..=grid_size.x).cartesian_product(0..=grid_size.x) {
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
            if x == 0 || x == grid_size.x || y == 0 || y == grid_size.y {
                infinite[*min_index] = true;
            }
            sizes[*min_index] += 1;
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

pub fn part2(
    coordinates: &[Coord],
    grid_size: &GridSize,
    safe_distance: u32,
) -> Result<usize, AocError> {
    let mut count = 0usize;
    for (y, x) in (0..=grid_size.y).cartesian_product(0..=grid_size.x) {
        let distance: u32 = coordinates.iter().map(|c| c.distance(x, y)).sum();

        if distance < safe_distance {
            count += 1;
        }
    }

    Ok(count)
}

#[cfg(test)]
mod tests {
    use crate::{GridSize, calc_grid_size};

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
    fn test_grid_size() {
        let input = parse(DATA).unwrap();
        let result = calc_grid_size(&input).unwrap();
        assert_eq!(result, GridSize::new(8, 9));
    }

    #[test]
    fn test_part_1() {
        let input = parse(DATA).unwrap();
        let gs = calc_grid_size(&input).unwrap();
        let result = part1(&input, &gs).unwrap();
        assert_eq!(17, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse(DATA).unwrap();
        let gs = calc_grid_size(&input).unwrap();
        let result = part2(&input, &gs, 32).unwrap();
        assert_eq!(16, result);
    }
}
