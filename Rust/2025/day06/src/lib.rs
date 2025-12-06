pub mod part1;
pub mod part2;

#[derive(Debug)]
pub enum Operator {
    Multiply,
    Add,
}

impl std::str::FromStr for Operator {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Ok(match s {
            "*" => Operator::Multiply,
            "+" => Operator::Add,
            _ => unreachable!("Invalid operator '{s}'"),
        })
    }
}
