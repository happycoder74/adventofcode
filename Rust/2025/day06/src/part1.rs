#![allow(unused_variables)]
use crate::Operator;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let rows = input.lines().map(str::trim).collect::<Vec<_>>();
    let operators: Vec<Operator> = rows
        .iter()
        .last()
        .unwrap()
        .split_whitespace()
        .map(|s| s.parse::<Operator>().unwrap())
        .collect();
    let operands = rows
        .iter()
        .take(rows.len() - 1)
        .map(|s| {
            s.split_whitespace()
                .map(|n| n.parse::<usize>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let mut result = 0usize;
    for icol in 0..operands[0].len() {
        let column = operands.iter().map(|v| v[icol]);
        result += match &operators[icol] {
            Operator::Multiply(x) => column.fold(*x, |acc, v| acc * v),
            Operator::Add(x) => column.fold(*x, |acc, v| acc * v),
        }
    }

    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +  ";

        assert_eq!(super::solve_part(input).unwrap(), 4_277_556);
    }
}
