#![allow(unused_variables)]
use std::error::Error;

use crate::Grid;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
#[allow(clippy::cast_possible_truncation)]
pub fn solve_part(input: &str) -> Result<usize, Box<dyn Error>> {
    let mut grid = Grid::new();
    let lines = input.lines().map(str::trim).zip(0i32..).collect::<Vec<_>>();
    for (row, irow) in &lines {
        row.chars().zip(0i32..).for_each(|(col, icol)| {
            if col == '@' {
                grid.grid.insert((*irow, icol));
            }
        });
    }

    Ok(grid.accessible())
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.";

        assert_eq!(super::solve_part(input).unwrap(), 13);
    }
}
