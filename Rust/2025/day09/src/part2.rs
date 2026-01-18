#![allow(unused_variables)]
use std::cmp::{max, min};

use aoc_utils::{Location, NotImplementedError};
use itertools::Itertools;

// With inspiration taken from prositen/advent-of-code
struct Rectangle {
    x_min: usize,
    y_min: usize,
    x_max: usize,
    y_max: usize,
}

impl Rectangle {
    fn new(l1: &Location<usize>, l2: &Location<usize>) -> Self {
        let x0 = l1.x;
        let y0 = l1.y;
        let x1 = l2.x;
        let y1 = l2.y;

        Self {
            x_min: min(x0, x1),
            x_max: max(x0, x1),
            y_min: min(y0, y1),
            y_max: max(y0, y1),
        }
    }

    fn area(&self) -> usize {
        (1 + self.x_max - self.x_min) * (1 + self.y_max - self.y_min)
    }

    fn intersects(&self, other: &Self) -> bool {
        !(self.x_max <= other.x_min
            || self.x_min >= other.x_max
            || self.y_max <= other.y_min
            || self.y_min >= other.y_max)
    }
}

#[allow(unused)]
fn area(l1: &Location<usize>, l2: &Location<usize>) -> impl num::Integer {
    (1 + l1.x.abs_diff(l2.x)) * (1 + l1.y.abs_diff(l2.y))
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut red_tiles: Vec<_> = input
        .lines()
        .map(|line| line.trim().parse::<Location<usize>>().unwrap())
        .collect();
    red_tiles.push(red_tiles[0]);
    let mut borders = red_tiles
        .iter()
        .tuple_windows()
        .map(|(l1, l2)| Rectangle::new(l1, l2))
        .collect::<Vec<_>>();

    borders.sort_by_key(Rectangle::area);

    let mut combinations = red_tiles
        .iter()
        .combinations(2)
        .map(|v| Rectangle::new(v[0], v[1]))
        .collect::<Vec<_>>();

    combinations.sort_by_key(Rectangle::area);

    for rectangle in combinations.iter().rev() {
        let intersects = borders.iter().any(|b| rectangle.intersects(b));
        if !intersects {
            return Ok(rectangle.area());
        }
    }
    Err(NotImplementedError)
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

        assert_eq!(super::solve_part(input).unwrap(), 24);
    }
}
