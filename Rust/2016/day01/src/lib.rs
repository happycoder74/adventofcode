use std::num::ParseIntError;

pub mod part1;
pub mod part2;

pub enum Instruction {
    Left(i32),
    Right(i32),
}

pub enum Direction {
    North,
    West,
    South,
    East,
}

#[derive(Default, Eq, Hash, PartialEq, Clone)]
pub struct Position {
    x: i32,
    y: i32,
}

impl Position {
    pub fn manhattan_distance(&self) -> i32 {
        self.x.abs() + self.y.abs()
    }
}

impl std::str::FromStr for Instruction {
    type Err = ParseIntError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut comm = s.chars();
        let turn = comm.next();
        let steps: i32 = comm.collect::<String>().parse::<i32>()?;
        match turn {
            Some(x) => match x {
                'R' => Ok(Instruction::Right(steps)),
                'L' => Ok(Instruction::Left(steps)),
                _ => unreachable!("Invalid instruction"),
            },
            None => unreachable!("Invalid instruction"),
        }
    }
}
