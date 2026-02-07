use std::{collections::HashSet, str::FromStr};

use aoc_utils::AocError;

#[derive(Debug, PartialEq)]
pub enum Instruction {
    Up(u32),
    Down(u32),
    Left(u32),
    Right(u32),
}

impl FromStr for Instruction {
    type Err = AocError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.split_once(' ') {
            Some(("R", x)) => Ok(Instruction::Right(
                x.parse::<u32>().map_err(|_| AocError::new("ParseError"))?,
            )),
            Some(("L", x)) => Ok(Instruction::Left(
                x.parse::<u32>().map_err(|_| AocError::new("ParseError"))?,
            )),
            Some(("U", x)) => Ok(Instruction::Up(
                x.parse::<u32>().map_err(|_| AocError::new("ParseError"))?,
            )),
            Some(("D", x)) => Ok(Instruction::Down(
                x.parse::<u32>().map_err(|_| AocError::new("ParseError"))?,
            )),
            Some(_) | None => Err(AocError::new("ParseError")),
        }
    }
}

pub fn parse_input(input: &str) -> Result<Vec<Instruction>, AocError> {
    input.lines().map(str::parse).collect()
}

type Coord = (i32, i32);

struct Snake {
    segments: Vec<Coord>,
    tail_positions: HashSet<Coord>,
}

impl Snake {
    fn new(segments: usize) -> Self {
        Self {
            segments: vec![(0, 0); segments],
            tail_positions: HashSet::new(),
        }
    }

    fn adjust_snake(&mut self) {
        for segment in 1..self.segments.len() {
            let (dx, dy) = (
                self.segments[segment - 1].0 - self.segments[segment].0,
                self.segments[segment - 1].1 - self.segments[segment].1,
            );
            if dx.abs() > 1 || dy.abs() > 1 {
                self.segments[segment].0 += dx.signum();
                self.segments[segment].1 += dy.signum();
            }
        }
    }

    fn solve(&mut self, input: &[Instruction]) -> Result<usize, AocError> {
        let head = 0usize;
        let tail: usize = self.segments.len() - 1;
        self.tail_positions.insert(self.segments[tail]);
        for instruction in input {
            let (x, delta) = match instruction {
                Instruction::Up(x) => (x, (0, 1)),

                Instruction::Down(x) => (x, (0, -1)),
                Instruction::Left(x) => (x, (1, 0)),
                Instruction::Right(x) => (x, (-1, 0)),
            };
            for _ in 0..*x {
                self.segments[head].0 += delta.0;
                self.segments[head].1 += delta.1;
                self.adjust_snake();
                self.tail_positions.insert(self.segments[tail]);
            }
        }

        Ok(self.tail_positions.len())
    }
}

pub fn solve_part_1(input: &[Instruction]) -> Result<usize, AocError> {
    let mut snake = Snake::new(2);
    snake.solve(input)
}

pub fn solve_part_2(input: &[Instruction]) -> Result<usize, AocError> {
    let mut snake = Snake::new(10);
    snake.solve(input)
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
