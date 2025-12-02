use std::error::Error;
use std::fmt::Display;

pub mod part1;
pub mod part2;

#[derive(Debug)]
pub struct NotImplementedError {
    text: String,
}

impl NotImplementedError {
    #[allow(clippy::must_use_candidate)]
    pub fn new(value: &str) -> Self {
        Self {
            text: value.to_string(),
        }
    }
}

impl Error for NotImplementedError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        None
    }
}

impl Display for NotImplementedError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.text)
    }
}

#[derive(Copy, Clone, Debug, Eq, PartialEq)]
pub enum Instruction {
    Left(i32),
    Right(i32),
}

impl std::str::FromStr for Instruction {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let amount = s[1..].parse().unwrap();

        Ok(match &s[..1] {
            "L" => Instruction::Left(amount),
            "R" => Instruction::Right(amount),
            _ => unreachable!("Invalid instruction"),
        })
    }
}
