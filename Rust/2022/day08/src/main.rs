use std::{
    collections::{HashMap, HashSet},
    ops::BitOr,
};

use aoc_utils::{AocError, aoc_get_data};
struct Forest {
    grid: HashMap<(usize, usize), u32>,
    max_row: usize,
    max_col: usize,
}

fn parse_input(input: &str) -> Result<Forest, AocError> {
    let mut grid = HashMap::new();
    input.lines().enumerate().for_each(|(irow, row)| {
        row.chars().enumerate().for_each(|(icol, col)| {
            grid.insert((irow, icol), col.to_digit(10).unwrap());
        })
    });
    let (max_row, _) = grid.keys().max_by_key(|&&v| v.0).unwrap();
    let (_, max_col) = grid.keys().max_by_key(|&&v| v.1).unwrap();
    Ok(Forest {
        max_row: *max_row,
        max_col: *max_col,
        grid,
    })
}

fn look_from_left(f: &Forest) -> HashSet<(usize, usize)> {
    let mut visible_left = HashSet::new();
    for row in 1..f.max_row {
        let mut highest = f.grid.get(&(row, 0)).expect("All keys should exist");
        for col in 1..f.max_col {
            let tree = f.grid.get(&(row, col)).unwrap();
            if tree > highest {
                visible_left.insert((row, col));
                highest = tree;
            }
        }
    }

    return visible_left;
}

fn look_from_right(f: &Forest) -> HashSet<(usize, usize)> {
    let mut visible = HashSet::new();
    for row in 1..f.max_row {
        let mut highest = f
            .grid
            .get(&(row, f.max_col))
            .expect("All keys should exist");
        for col in (1..f.max_col).rev() {
            let tree = f.grid.get(&(row, col)).unwrap();
            if tree > highest {
                visible.insert((row, col));
                highest = tree;
            }
        }
    }

    return visible;
}

fn look_from_top(f: &Forest) -> HashSet<(usize, usize)> {
    let mut visible = HashSet::new();
    for col in 1..f.max_col {
        let mut highest = f.grid.get(&(0, col)).expect("All keys should exist");
        for row in 1..f.max_row {
            let tree = f.grid.get(&(row, col)).unwrap();
            if tree > highest {
                visible.insert((row, col));
                highest = tree;
            }
        }
    }

    return visible;
}

fn look_from_bottom(f: &Forest) -> HashSet<(usize, usize)> {
    let mut visible = HashSet::new();
    for col in 1..f.max_col {
        let mut highest = f
            .grid
            .get(&(f.max_row, col))
            .expect("All keys should exist");
        for row in (1..f.max_row).rev() {
            let tree = f.grid.get(&(row, col)).unwrap();
            if tree > highest {
                visible.insert((row, col));
                highest = tree;
            }
        }
    }

    return visible;
}

fn solve_part_1(f: &Forest) -> Result<usize, AocError> {
    // Look from left
    let visible_left = look_from_left(&f);
    let visible_right = look_from_right(&f);
    let visible_top = look_from_top(&f);
    let visible_bottom = look_from_bottom(&f);

    let visible = visible_left
        .bitor(&visible_right)
        .bitor(&visible_top)
        .bitor(&visible_bottom);

    Ok(visible.len() + 2 * f.max_row + 2 * f.max_col)
}

fn solve_part_2(f: &Forest) -> Result<usize, AocError> {
    Err(AocError::new("Not implemented"))
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "08");
    let start = std::time::Instant::now();
    let input = parse_input(input).unwrap();
    println!("Prep time: {:?}", start.elapsed());

    let start = std::time::Instant::now();
    match solve_part_1(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}
#[cfg(test)]
mod tests {
    use super::*;
    const DATA: &str = "30373
25512
65332
33549
35390";

    #[test]
    fn test_visible_left() {
        let forest = parse_input(DATA).unwrap();
        let vl = look_from_left(&forest);
        println!("{vl:?}");
        assert_eq!(2, vl.len());
    }

    #[test]
    fn test_visible_right() {
        let forest = parse_input(DATA).unwrap();
        let vr = look_from_right(&forest);
        println!("{vr:?}");
        assert_eq!(3, vr.len());
    }

    #[test]
    fn test_visible_top() {
        let forest = parse_input(DATA).unwrap();
        let vt = look_from_top(&forest);
        println!("{vt:?}");

        assert_eq!(2, vt.len());
    }

    #[test]
    fn test_visible_bottom() {
        let forest = parse_input(DATA).unwrap();
        let vb = look_from_bottom(&forest);
        println!("{vb:?}");

        assert_eq!(1, vb.len());
    }

    #[test]
    fn test_part_1() {
        let forest = parse_input(DATA).unwrap();
        let visible = solve_part_1(&forest);
        assert_eq!(21, visible);
    }
}
