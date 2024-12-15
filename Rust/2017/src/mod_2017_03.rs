use itertools::Itertools;
use std::collections::HashMap;

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
struct Pos {
    x: i32,
    y: i32,
}

fn next_step(pos: Pos) -> Pos {
    let Pos { mut x, mut y } = pos;

    if (x > 0) && (x.abs() > y.abs()) {
        y += 1;
    } else if (x < 0) && ((x.abs() > y.abs()) || (x == -y)) {
        y -= 1;
    } else if (y > 0) && ((y.abs() > x.abs()) || (x == y)) {
        x -= 1;
    } else {
        x += 1;
    }

    return Pos { x, y };
}

fn sum_neighbours(pos: Pos, grid: &HashMap<Pos, u32>) -> u32 {
    (-1..=1)
        .cartesian_product(-1..=1)
        .map(|(dx, dy)| {
            let p = Pos {
                x: pos.x + dx,
                y: pos.y + dy,
            };
            grid.get(&p).unwrap_or(&0)
        })
        .sum()
}

pub fn solve_part_1(input: &str) -> (i32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let target: i32 = input.trim().parse().unwrap();
    let mut pos = Pos { x: 0, y: 0 };

    for _ in 1..target {
        pos = next_step(pos);
    }
    let result = pos.x.abs() + pos.y.abs();
    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}

pub fn solve_part_2(input: &str) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let target: u32 = input.trim().parse().unwrap();
    let mut pos = Pos { x: 0, y: 0 };
    let mut grid = HashMap::new();

    grid.insert(pos, 1);
    let result = loop {
        pos = next_step(pos);
        let val = sum_neighbours(pos, &grid);
        grid.insert(pos, val);
        if val > target {
            break val;
        }
    };

    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_next_step_first() {
        let pos = Pos { x: 0, y: 0 };
        assert_eq!(Pos { x: 1, y: 0 }, next_step(pos));
    }

    #[test]
    fn test_next_step_2() {
        let pos = Pos { x: 1, y: 0 };
        assert_eq!(Pos { x: 1, y: 1 }, next_step(pos));
    }

    #[test]
    fn test_next_step_3() {
        let pos = Pos { x: 1, y: 1 };
        assert_eq!(Pos { x: 0, y: 1 }, next_step(pos));
    }

    #[test]
    fn test_part_1_1() {
        assert_eq!(3, solve_part_1("12").0);
    }

    #[test]
    fn test_part_1_2() {
        assert_eq!(2, solve_part_1("23").0);
    }

    #[test]
    fn test_part_1_3() {
        assert_eq!(31, solve_part_1("1024").0);
    }

    #[test]
    fn test_part_2_1() {
        assert_eq!(2, solve_part_2("1").0);
    }

    #[test]
    fn test_part_2_2() {
        assert_eq!(59, solve_part_2("57").0);
    }

    #[test]
    fn test_part_2_3() {
        assert_eq!(747, solve_part_2("362").0);
    }
}
