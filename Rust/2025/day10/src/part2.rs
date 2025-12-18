#![allow(unused_variables)]
use microlp::{LinearExpr, OptimizationDirection, Problem};
use std::num::ParseIntError;
use std::str::FromStr;

use thiserror::Error;

#[derive(Debug, Error)]
enum ParseError {
    #[error("Syntax error")]
    SyntaxError,
    #[error(transparent)]
    InvalidNumber(#[from] ParseIntError),
}

#[derive(Debug, Clone, PartialEq, Eq)]
struct Machine {
    indicator_lights: u16,
    buttons: Vec<u16>,
    joltage: Vec<u16>,
}

impl FromStr for Machine {
    type Err = ParseError;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let rest = s.strip_prefix('[').ok_or(ParseError::SyntaxError)?;
        let (indicator_lights, rest) = rest.split_once("] ").ok_or(ParseError::SyntaxError)?;
        let indicator_lights = indicator_lights
            .bytes()
            .enumerate()
            .fold(0, |bits, (pos, ch)| bits | u16::from(ch & 1) << pos);
        let (buttons, rest) = rest.split_once(" {").ok_or(ParseError::SyntaxError)?;
        let buttons = buttons
            .split(' ')
            .map(|btn| {
                btn.strip_prefix('(')
                    .ok_or(ParseError::SyntaxError)?
                    .strip_suffix(')')
                    .ok_or(ParseError::SyntaxError)?
                    .split(',')
                    .try_fold(0_u16, |mask, light| Ok(mask | (1 << light.parse::<u8>()?)))
            })
            .collect::<Result<_, ParseError>>()?;
        let joltage = rest
            .strip_suffix('}')
            .ok_or(ParseError::SyntaxError)?
            .split(',')
            .map(str::parse)
            .collect::<Result<_, _>>()?;
        Ok(Self {
            indicator_lights,
            buttons,
            joltage,
        })
    }
}

fn minimum_presses(buttons: &[u16], joltage: &[u16]) -> u64 {
    let mut problem = Problem::new(OptimizationDirection::Minimize);
    let target_max: u16 = joltage.iter().copied().max().unwrap();
    let button_vars = buttons
        .iter()
        .map(|_| problem.add_integer_var(1.0, (0, i32::from(target_max))))
        .collect::<Vec<_>>();

    for (light_ix, &trg) in joltage.iter().enumerate() {
        let mut expr = LinearExpr::empty();
        for (btn_mask, &btn_var) in buttons.iter().zip(&button_vars) {
            if btn_mask & (1 << light_ix) != 0 {
                expr.add(btn_var, 1.0);
            }
        }
        problem.add_constraint(expr, microlp::ComparisonOp::Eq, f64::from(trg));
    }

    let solution = problem.solve().expect("Any solution");
    solution.objective().round() as u64
}

fn parse(input: &str) -> Result<Vec<Machine>, ParseError> {
    input.lines().map(str::parse).collect()
}

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<u64, Box<dyn std::error::Error>> {
    let parsed_input = parse(input)?;
    let mut result = 0;

    for instruction in &parsed_input {
        result += minimum_presses(&instruction.buttons, &instruction.joltage);
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
