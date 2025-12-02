pub mod part1;
pub mod part2;

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
