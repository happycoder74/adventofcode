pub struct Position {
    x: usize,
    y: usize,
}

impl Position {
    pub fn new(x: usize, y: usize) -> Self {
        Self { x: x, y: y }
    }
}

pub enum Instruction {
    Up,
    Down,
    Left,
    Right,
}

pub fn parse_input(input: &str) -> Vec<Vec<Instruction>> {
    let lines: Vec<&str> = input.lines().collect();
    // let instructions: Vec<Vec<Instruction>> = vec!["ULL", "RRDDD", "LURDL", "UUUUD"]
    lines
        .iter()
        .map(|row| {
            row.chars()
                .map(|c: char| match c {
                    'U' => Instruction::Up,
                    'D' => Instruction::Down,
                    'L' => Instruction::Left,
                    'R' => Instruction::Right,
                    _ => unreachable!("Invalid instruction"),
                })
                .collect()
        })
        .collect()
}

pub mod part1;
pub mod part2;
