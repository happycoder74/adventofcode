use std::collections::HashSet;

use aoc_utils::AocError;

#[derive(Debug, PartialEq)]
pub enum Instruction {
    Up(u32),
    Down(u32),
    Left(u32),
    Right(u32),
}

pub fn parse_input(input: &str) -> Result<Vec<Instruction>, AocError> {
    let instructions = input
        .lines()
        .map(|line| match line.split_once(' ') {
            Some(("R", x)) => Instruction::Right(x.parse::<u32>().unwrap()),
            Some(("L", x)) => Instruction::Left(x.parse::<u32>().unwrap()),
            Some(("U", x)) => Instruction::Up(x.parse::<u32>().unwrap()),
            Some(("D", x)) => Instruction::Down(x.parse::<u32>().unwrap()),
            Some(_) | None => unreachable!(),
        })
        .collect::<Vec<_>>();

    Ok(instructions)
}

fn adjust_snake(positions: &mut Vec<(i32, i32)>) {
    for segment in 1..positions.len() {
        let (dx, dy) = (
            positions[segment - 1].0 - positions[segment].0,
            positions[segment - 1].1 - positions[segment].1,
        );
        if (dx.abs() + dy.abs()) > 2 {
            // Move diagonally
            positions[segment].0 += dx / dx.abs();
            positions[segment].1 += dy / dy.abs();
        } else if dy == 0 && dx.abs() > 1 {
            positions[segment].0 += dx / dx.abs();
        } else if dx == 0 && dy.abs() > 1 {
            positions[segment].1 += dy / dy.abs();
        }
    }
}

fn solver(input: &[Instruction], segments: usize) -> Result<usize, AocError> {
    let mut tail_positions: HashSet<(i32, i32)> = HashSet::new();
    let head = 0usize;
    let tail: usize = segments - 1;
    let mut positions = vec![(0, 0); segments];

    tail_positions.insert(positions[tail]);
    if segments > 2 {
        //     println!("== Initial State ==\n\n");
        // print_snake(&positions, 30, 30);
    }
    for instruction in input {
        let (x, delta) = match instruction {
            Instruction::Up(x) => (x, (0, 1)),

            Instruction::Down(x) => (x, (0, -1)),
            Instruction::Left(x) => (x, (1, 0)),
            Instruction::Right(x) => (x, (-1, 0)),
        };
        for _ in 0..*x {
            positions[head].0 += delta.0;
            positions[head].1 += delta.1;
            adjust_snake(&mut positions);
            tail_positions.insert(positions[tail]);
        }
    }

    Ok(tail_positions.len())
}

pub fn solve_part_1(input: &[Instruction]) -> Result<usize, AocError> {
    solver(input, 2)
}

pub fn solve_part_2(input: &[Instruction]) -> Result<usize, AocError> {
    solver(input, 10)
}

#[cfg(test)]
mod tests {
    const DATA: &str = "R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2";

    const DATA_LARGER: &str = "R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20";

    use super::*;

    #[test]
    fn test_parse_input() {
        let result = parse_input(DATA).unwrap();
        let expected = vec![
            Instruction::Right(4),
            Instruction::Up(4),
            Instruction::Left(3),
            Instruction::Down(1),
            Instruction::Right(4),
            Instruction::Down(1),
            Instruction::Left(5),
            Instruction::Right(2),
        ];

        assert_eq!(result, expected);
    }

    #[test]
    fn test_solve_part_1() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_1(&input).unwrap();
        assert_eq!(13, result);
    }

    #[test]
    fn test_solve_part_2() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!(1, result);
    }

    #[test]
    fn test_solve_part_2_larger() {
        let input = parse_input(DATA_LARGER).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!(36, result);
    }
}
