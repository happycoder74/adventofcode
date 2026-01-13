pub mod part1;
pub mod part2;

#[derive(Debug)]
pub enum Operator {
    Multiply(usize),
    Add(usize),
}

#[derive(Debug, PartialEq, Eq)]
pub struct ParseOperatorError;

impl std::str::FromStr for Operator {
    type Err = ParseOperatorError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "*" => Ok(Operator::Multiply(1)),
            "+" => Ok(Operator::Add(0)),
            _ => Err(ParseOperatorError),
        }
    }
}
