#![allow(unused)]
use std::{
    collections::HashSet,
    fmt::{Debug, Display},
    iter::zip,
    str::FromStr,
};

use anyhow::{Error, Result};
type Grid = [[bool; 3]; 3];

pub mod part1;
pub mod part2;

#[derive(Debug)]
pub enum AocError {
    ParseError,
}

impl std::error::Error for AocError {}

impl Display for AocError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "ParseError")
    }
}

#[derive(Debug)]
pub struct Package {
    id: i32,
    grid: Grid,
    occupancy: i32,
    variations: HashSet<Grid>,
}

impl Package {
    fn new() -> Self {
        Self {
            id: 0,
            grid: [[false; 3]; 3],
            occupancy: 0,
            variations: HashSet::new(),
        }
    }
}

impl FromStr for Package {
    type Err = AocError;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let mut p = Package::new();
        let mut lines = s.lines().map(str::trim);
        let id: i32 = lines.next().unwrap().split_at(1).0.parse().unwrap();
        let mut grid = [[false; 3]; 3];
        let tmp = 0..3;
        for grid_line in tmp {
            let line = lines.next().unwrap();
            for (i, c) in line.chars().enumerate() {
                grid[grid_line][i] = match c {
                    '#' => true,
                    '.' => false,
                    _ => return Err(AocError::ParseError),
                }
            }
        }
        p.id = id;
        p.grid = grid;
        p.occupancy = p.occupied();
        p.variations = p.variations();
        Ok(p)
    }
}

fn flip_horizontal(grid: Grid) -> Grid {
    let mut g = grid;
    (0..3).for_each(|row| {
        g[row].swap(0, 2);
    });
    g
}
fn flip_vertical(grid: Grid) -> Grid {
    let mut g = grid;

    g.swap(0, 2);
    g
}

fn rotate_right(grid: Grid) -> Grid {
    let mut g = grid;
    (0..3).for_each(|r| {
        let mut tmp = 0..3;
        for c in tmp {
            g[r][c] = grid[2 - c][r];
        }
    });

    g
}
impl Package {
    fn occupied(&self) -> i32 {
        let mut occ = 0;
        for r in 0..3 {
            for c in 0..3 {
                if self.grid[r][c] {
                    occ += 1;
                }
            }
        }
        occ
    }

    fn variations(&self) -> HashSet<Grid> {
        let mut variations = HashSet::new();
        variations.insert(self.grid);
        variations.insert(flip_horizontal(self.grid));
        variations.insert(flip_vertical(self.grid));
        let mut g = self.grid;
        for _ in 0..3 {
            g = rotate_right(g);
            variations.insert(g);
            variations.insert(flip_horizontal(g));
            variations.insert(flip_vertical(g));
        }

        variations
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rotate_1() {
        let mut grid = [
            [true, true, false],
            [true, false, false],
            [true, true, false],
        ];

        let grid_rotated = rotate_right(grid);
        assert_eq!(
            grid_rotated,
            [
                [true, true, true],
                [true, false, true],
                [false, false, false]
            ]
        );
    }
    #[test]
    fn test_rotate_2() {
        let mut grid = [
            [true, false, false],
            [true, true, false],
            [true, true, true],
        ];

        let grid_rotated = rotate_right(grid);
        assert_eq!(
            grid_rotated,
            [
                [true, true, true],
                [true, true, false],
                [true, false, false]
            ]
        );
    }
}

#[derive(Debug)]
pub struct Region {
    x_size: i32,
    y_size: i32,
    packages: [i32; 6],
    area: i32,
}

impl Region {
    fn space(&self) -> i32 {
        self.x_size * self.y_size
    }
}

#[derive(Debug)]
pub struct PlayingField {
    packages: Vec<Package>,
    regions: Vec<Region>,
}

pub fn parse_packages(input: &str) -> Result<PlayingField> {
    let packages: Vec<_> = input
        .split("\n\n")
        .take(6)
        .map(|s| s.parse::<Package>().unwrap())
        .collect();

    let mut regions = vec![];
    let mut items = [0i32; 6];

    let region_iter = input
        .split("\n\n")
        .last()
        .unwrap()
        .lines()
        .map(str::trim)
        .map(|line| line.split(':'));

    for mut region in region_iter {
        let mut size = region
            .next()
            .unwrap()
            .split('x')
            .map(|s| s.parse::<i32>().unwrap());
        let mut items_iter = region
            .next()
            .unwrap()
            .split_whitespace()
            .map(|n| n.parse::<i32>().unwrap());

        (0..6).for_each(|ele| {
            items[ele] = items_iter.next().unwrap();
        });

        let x_size = size.next().unwrap();
        let y_size = size.next().unwrap();
        regions.push(Region {
            x_size,
            y_size,
            packages: items,
            area: x_size * y_size,
        });
    }

    let field = PlayingField { packages, regions };

    Ok(field)
}

fn print_grid(grid: &Grid) {
    println!(
        "{}{}{}",
        if grid[0][0] { '#' } else { '.' },
        if grid[0][1] { '#' } else { '.' },
        if grid[0][2] { '#' } else { '.' },
    );
    println!(
        "{}{}{}",
        if grid[1][0] { '#' } else { '.' },
        if grid[1][1] { '#' } else { '.' },
        if grid[1][2] { '#' } else { '.' },
    );
    println!(
        "{}{}{}",
        if grid[2][0] { '#' } else { '.' },
        if grid[2][1] { '#' } else { '.' },
        if grid[2][2] { '#' } else { '.' },
    );
    println!();
}
