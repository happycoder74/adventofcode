#![allow(unused_variables)]
use std::collections::HashMap;
use std::collections::VecDeque;

use crate::Instruction;
use crate::Lights;
use crate::Result;

fn parse_input(input: &str) -> Result<Vec<Instruction>> {
    let instructions: Result<Vec<Instruction>> = input
        .lines()
        .map(str::trim)
        .map(|line| line.parse::<Instruction>().map_err(|e| e.into()))
        .collect();
    instructions
}

fn minimum_presses(instruction: &Instruction) -> usize {
    let mut to_visit = VecDeque::new();
    let current_lights = Lights::init(instruction);
    to_visit.push_back((current_lights, 0));

    let mut seen_states: HashMap<Lights, usize> = HashMap::new();

    while let Some((state, pushes)) = to_visit.pop_front() {
        for button in &instruction.buttons {
            let next_state = button.apply(&state);
            if next_state.lights == *instruction.lights {
                return pushes + 1;
            } else if seen_states.contains_key(&next_state) {
                continue;
            }

            seen_states.insert(next_state.clone(), pushes);
            to_visit.push_back((next_state, pushes + 1))
        }
    }

    0
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize> {
    let parsed_input = parse_input(input)?;
    let mut result = 0;

    for instruction in &parsed_input {
        result += minimum_presses(instruction);
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
