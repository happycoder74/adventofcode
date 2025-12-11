#![allow(unused_variables)]
use aoc_utils::NotImplementedError;

// With inspiration taken from prositen/advent-of-code

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    Err(NotImplementedError)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3";

        assert_eq!(super::solve_part(input).unwrap(), 0);
    }
}
