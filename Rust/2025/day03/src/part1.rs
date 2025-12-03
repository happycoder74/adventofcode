use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<u32, NotImplementedError> {
    let mut result = 0;
    let batteries: Vec<Vec<_>> = input
        .lines()
        .map(str::trim)
        .map(|s| {
            s.chars()
                .map(|c| c.to_digit(10).unwrap())
                .collect::<Vec<u32>>()
        })
        .collect();

    for battery in batteries {
        let max_index = battery.len() - 1;
        let (index, voltage) = battery
            .iter()
            .enumerate()
            .rev()
            .max_by_key(|&(_, val)| val)
            .unwrap();
        if index == max_index - 1 {
            result += voltage * 10 + battery.iter().last().unwrap();
        } else if index == max_index {
            result += battery
                .iter()
                .enumerate()
                .take(index)
                .max_by_key(|(_, v)| *v)
                .unwrap()
                .1
                * 10
                + voltage;
        } else {
            result += voltage * 10
                + battery
                    .iter()
                    .enumerate()
                    .skip(index + 1)
                    .max_by_key(|(_, v)| *v)
                    .unwrap()
                    .1;
        }
    }
    Ok(result)
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
