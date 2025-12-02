use aoc_utils::NotImplementedError;
use itertools::Itertools;

#[allow(clippy::missing_panics_doc, clippy::missing_errors_doc)]
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
            for sizes in 1..=(val_str.len() / 2) {
                // let mut parts = val_str.chars().chunks(sizes).into_iter();
                let check = val_str
                    .chars()
                    .chunks(sizes)
                    .into_iter()
                    .map(std::iter::Iterator::collect::<Vec<char>>)
                    .all_equal();
                if check {
                    result += val;
                    break;
                }
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
