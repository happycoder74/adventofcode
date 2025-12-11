#![allow(unused_variables)]
use crate::Operator;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let rows = input
        .lines()
        .map(|s| s.chars().rev().collect::<String>())
        .collect::<Vec<_>>();
    let operators: Vec<Operator> = rows
        .iter()
        .last()
        .unwrap()
        .split_whitespace()
        .map(|s| s.parse::<Operator>().unwrap())
        .collect();

    let reversed_text = rows
        .iter()
        .take(rows.len() - 1)
        .map(|s| s.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();
    // Build columns instead
    let mut columns = vec![];
    for col in 0..reversed_text[0].len() {
        let column = reversed_text.iter().map(|row| row[col]).collect::<Vec<_>>();
        columns.push(column);
    }
    let result = columns
        .split(|v| v == &vec![' '; rows.len() - 1])
        .map(|v| {
            v.iter()
                .map(|vv| {
                    vv.iter()
                        .collect::<String>()
                        .trim()
                        .parse::<usize>()
                        .unwrap_or(0usize)
                })
                .collect::<Vec<_>>()
        })
        .enumerate()
        .map(|(i, op)| match operators[i] {
            Operator::Multiply(x) => op.iter().fold(x, |acc, v| acc * v),
            Operator::Add(x) => op.iter().fold(x, |acc, v| acc + v),
        })
        .sum::<usize>();

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

        assert_eq!(super::solve_part(input).unwrap(), 3_263_827);
    }
}
