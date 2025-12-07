#![allow(unused_variables)]
use std::collections::{HashSet, VecDeque};

use crate::Grid;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut grid = Grid::import(input);
    let start = grid.grid.iter().find(|&(k, &v)| v == 'S').unwrap().0;

    let mut visited = HashSet::new();
    let mut to_visit = VecDeque::new();
    let mut split_counter = 0usize;

    to_visit.push_back(start.step_down());
    while !to_visit.is_empty() {
        let loc = to_visit.pop_back().unwrap();
        if !visited.contains(&loc) {
            visited.insert(loc);
            match grid.grid.get(&loc) {
                Some(x) => match x {
                    '^' => {
                        let loc_left = loc.step(-1, 0);
                        to_visit.push_back(loc_left);
                        let loc_right = loc.step(1, 0);
                        to_visit.push_back(loc_right);
                        split_counter += 1;
                    }
                    '.' => {
                        grid.grid.insert(loc, '|');
                        to_visit.push_back(loc.step_down());
                    }
                    '|' => {
                        println!("Hmmmm ({loc})");
                    }
                    _ => unreachable!(),
                },
                None => (),
            }
        }
    }
    // grid.print();
    Ok(split_counter)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = ".......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............";

        assert_eq!(super::solve_part(input).unwrap(), 21);
    }
}
