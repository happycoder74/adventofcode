use std::{collections::HashMap, error::Error, fmt::Display, str::FromStr};

pub mod part1;
pub mod part2;

#[derive(Debug)]
pub struct InstructionError;

impl Display for InstructionError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "InstructionError")
    }
}

impl Error for InstructionError {}

pub struct Instruction {
    source: String,
    destinations: Vec<String>,
}

impl Display for Instruction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}: {}", self.source, self.destinations.join(" "))
    }
}
impl FromStr for Instruction {
    type Err = InstructionError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut split = s.trim().split(": ");
        let source = split.next().unwrap().to_string();
        let destinations = split
            .next()
            .unwrap()
            .split_whitespace()
            .map(str::to_string)
            .collect();
        Ok(Instruction {
            source,
            destinations,
        })
    }
}
#[allow(clippy::missing_errors_doc)]
pub fn parse_input(input: &str) -> Result<HashMap<String, Vec<String>>, InstructionError> {
    let ret: Result<HashMap<String, Vec<String>>, _> = input
        .lines()
        .map(str::parse::<Instruction>)
        .map(|instr| match instr {
            Ok(instruction) => Ok((instruction.source, instruction.destinations)),
            Err(e) => Err(e),
        })
        .collect();
    ret
}
