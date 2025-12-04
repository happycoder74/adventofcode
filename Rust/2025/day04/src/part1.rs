#![allow(unused_variables)]
use crate::Grid;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut grid = Grid::new();
    let lines = input.lines().map(str::trim).enumerate().collect::<Vec<_>>();
    for (irow, row) in &lines {
        row.chars().enumerate().for_each(|(icol, col)| {
            if col == '@' {
                grid.grid.insert((*irow as i32, icol as i32));
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
