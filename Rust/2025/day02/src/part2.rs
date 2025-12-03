use aoc_utils::NotImplementedError;

#[allow(clippy::missing_panics_doc, clippy::missing_errors_doc)]
pub fn solve_part(input: &str) -> Result<u64, NotImplementedError> {
    let mut result = 0;
    let ranges = input.trim().split(|c| c == ',').map(|s| {
        let mut iter = s.splitn(2, |c| c == '-').map(|r| r.parse::<u64>().unwrap());
        (iter.next().unwrap(), iter.next().unwrap())
    });
    for (start, end) in ranges {
        for val in start..=end {
            let check = match val {
                10..=99 => val % 11 == 0,
                100..=999 => val % 111 == 0,
                1_000..=9_999 => val % 101 == 0 || val % 1_111 == 0,
                10_000..=99_999 => val % 11_111 == 0,
                100_000..=999_999 => val % 1_001 == 0 || val % 10_101 == 0 || val % 111_111 == 0,
                1_000_000..=9_999_999 => val % 1_111_111 == 0,
                10_000_000..=99_999_999 => {
                    val % 10_001 == 0 || val % 1_010_101 == 0 || val % 11_111_111 == 0
                }
                100_000_000..=999_999_999 => val % 1_001_001 == 0 || val % 111_111_111 == 0,
                1_000_000_000..=9_999_999_999 => {
                    val % 100_001 == 0 || val % 101_010_101 == 0 || val % 1_111_111_111 == 0
                }
                _ => false,
            };
            if check {
                result += val;
            }
        }
    }

    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

        assert_eq!(super::solve_part(input).unwrap(), 4_174_379_265);
    }
}
