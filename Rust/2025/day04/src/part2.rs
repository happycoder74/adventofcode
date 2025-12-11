#![allow(unused_variables)]
use crate::Grid;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut grid = Grid::new();
    let lines = input.lines().map(str::trim).zip(0i32..).collect::<Vec<_>>();
    let mut removable = 0;
    for (row, irow) in &lines {
        row.chars().zip(0i32..).for_each(|(col, icol)| {
            if col == '@' {
                grid.grid.insert((*irow, icol));
            }
        });
    }

    let size = grid.grid.len();
    loop {
        let removed = grid.remove_accessible();
        if removed == 0 {
            break;
        }
        removable += removed;
    }
    Ok(removable)
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

        assert_eq!(super::solve_part(input).unwrap(), 43);
    }
}
