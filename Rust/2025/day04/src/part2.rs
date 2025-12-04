#![allow(unused_variables)]
use aoc_utils::NotImplementedError;
use std::collections::HashSet;

fn count_neighbours(location: &(i32, i32), grid: &HashSet<(i32, i32)>) -> usize {
    let mut n_nb = 0;
    let (r, c) = location;
    for dr in -1..=1 {
        for dc in -1..=1 {
            if !((dc == 0) && (dr == 0)) {
                let nb = (r + dr, c + dc);
                if grid.contains(&nb) {
                    n_nb += 1;
                }
            }
        }
    }
    n_nb
}

fn count_paperrolls(grid: &HashSet<(i32, i32)>) -> usize {
    let result = grid
        .iter()
        .filter(|(r, c)| count_neighbours(&(*r, *c), &grid) < 4)
        .count();
    result
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut grid = HashSet::new();
    let lines = input.lines().map(str::trim).enumerate().collect::<Vec<_>>();
    let mut removable = 0;
    for (irow, row) in &lines {
        row.chars().enumerate().for_each(|(icol, col)| {
            if col == '@' {
                grid.insert((*irow as i32, icol as i32));
            }
        });
    }

    loop {
        let removable_locations = &grid
            .iter()
            .filter(|(r, c)| count_neighbours(&(*r, *c), &grid) < 4)
            .map(|(r, c)| (*r, *c))
            .collect::<Vec<_>>();
        if removable_locations.len() == 0 {
            break;
        }
        for (r, c) in removable_locations {
            removable += 1;
            grid.remove(&(*r, *c));
        }
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
