use aoc_utils::NotImplementedError;

#[allow(clippy::missing_panics_doc, clippy::missing_errors_doc)]
pub fn solve_part(input: &str) -> Result<u64, NotImplementedError> {
    let mut result = 0usize;
    let data = input
        .lines()
        .map(|line| {
            line.trim()
                .chars()
                .map(|c| c.to_digit(10).unwrap() as usize)
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    for bank in data {
        let mut bank_value = 0usize;
        let mut bank_line: &[usize] = &bank;

        for p in (0..12).rev() {
            let (index, max_item) = &bank_line[..bank_line.len() - p]
                .iter()
                .enumerate()
                .rev()
                .max_by_key(|(_, v)| *v)
                .unwrap();
            bank_line = &bank_line[index + 1..];
            bank_value += *max_item * 10usize.pow(p as u32);
        }
        result += bank_value;
    }
    Ok(result as u64)
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

        assert_eq!(super::solve_part(input).unwrap(), 3121910778619);
    }
}
