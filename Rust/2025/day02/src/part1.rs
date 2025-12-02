use crate::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<u64, NotImplementedError> {
    let mut result = 0;
    let ranges = input
        .trim()
        .split(',')
        .map(|s| s.split('-').map(|r| r.parse::<u64>().unwrap()));
    for mut r in ranges {
        let start: u64 = r.next().unwrap();
        let end: u64 = r.next().unwrap();
        for val in start..=end {
            let val_str = val.to_string();
            let parts = val_str.split_at(val_str.len() / 2);
            if parts.0 == parts.1 {
                result += val;
            }
        }
    }

    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests here
    #[test]
    fn test_solve_part() {
        let input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

        assert_eq!(super::solve_part(input).unwrap(), 1_227_775_554);
    }
}
