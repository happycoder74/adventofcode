use aoc_utils::NotImplementedError;

#[allow(clippy::missing_panics_doc, clippy::missing_errors_doc)]
pub fn solve_part(input: &str) -> Result<u64, NotImplementedError> {
    Err(NotImplementedError::new("Not implemented"))
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "987654321111111
811111111111119
234234234234278
818181911112111";

        assert_eq!(super::solve_part(input).unwrap(), 0);
    }
}
