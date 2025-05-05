use crate::AocResult;
use std::{error::Error, fmt::Display, time::Duration};

#[derive(Debug)]
pub struct AocError {
    value: String,
}

impl AocError {
    pub fn new(value: &str) -> Self {
        Self {
            value: value.to_string(),
        }
    }
}

impl Error for AocError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        None
    }
}

impl Display for AocError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.value)
    }
}

pub struct AocReturn {
    pub part1: Result<AocPartReturn, AocError>,
    pub part2: Result<AocPartReturn, AocError>,
}

impl AocReturn {
    pub fn from_parts(
        part1: Result<AocPartReturn, AocError>,
        part2: Result<AocPartReturn, AocError>,
    ) -> Self {
        AocReturn { part1, part2 }
    }
}

pub struct AocPartReturn {
    pub result: AocResult,
    pub duration: Duration,
}

pub trait Puzzle<T> {
    fn parse_input(input: &str) -> T;
    fn solve_part_1(input: &T) -> Result<AocPartReturn, AocError>;
    fn solve_part_2(input: &T) -> Result<AocPartReturn, AocError>;
    fn solve_all(self) -> AocReturn;
}
