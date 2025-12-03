use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let batteries = input
        .lines()
        .map(|s| s.trim().as_bytes())
        .map(|line| {
            let (i, a) = &line[..line.len() - 1]
                .iter()
                .enumerate()
                .rev()
                .max_by_key(|(_, v)| *v)
                .unwrap();
            let (_, b) = &line[*i + 1..]
                .iter()
                .enumerate()
                .rev()
                .max_by_key(|(_, v)| *v)
                .unwrap();
            ((*a - b'0') * 10 + *b - b'0') as usize
        })
        .sum::<usize>();

    Ok(batteries)
}

#[cfg(test)]
mod tests {
    // Unit tests here
    #[test]
    fn test_solve_part() {
        let input = "987654321111111
811111111111119
234234234234278
818181911112111";

        assert_eq!(super::solve_part(input).unwrap(), 357);
    }
}
