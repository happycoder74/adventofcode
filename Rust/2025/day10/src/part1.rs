#![allow(unused_variables)]
use crate::Instruction;
use crate::Result;
use crate::State;
use aoc_utils::NotImplementedError;

struct Lights {
    lights: Vec<State>,
}

impl Lights {
    fn init(instruction: &Instruction) -> Self {
        Self {
            lights: instruction.lights.iter().map(|_| State::Off).collect(),
        }
    }
}
fn parse_input(input: &str) -> Result<Vec<Instruction>> {
    let instructions: Result<Vec<Instruction>> = input
        .lines()
        .map(str::trim)
        .map(|line| line.parse::<Instruction>().map_err(|e| e.into()))
        .collect();
    instructions
}

fn minimum_presses(instruction: &Instruction, target: Lights) -> usize {
    0usize
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize> {
    let parsed_input = parse_input(input)?;
    let mut result = 0usize;

    for instruction in &parsed_input {
        let lights = Lights::init(instruction);
        let sub_result = minimum_presses(instruction, lights);
        result += sub_result;
    }
    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}";

        assert_eq!(super::solve_part(input).unwrap(), 7);
    }
}
