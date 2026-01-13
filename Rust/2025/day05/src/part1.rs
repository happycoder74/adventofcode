#![allow(unused_variables)]
use crate::Entry;
use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let mut ingredients = input.split("\n\n");
    let ranges = ingredients
        .next()
        .unwrap()
        .lines()
        .map(|s| {
            let mut iterator = s.trim().split('-').map(|n| n.parse::<usize>().unwrap());
            Entry {
                start: iterator.next().unwrap(),
                end: iterator.next().unwrap(),
            }
        })
        .collect::<Vec<_>>();

    let fresh = ingredients
        .next()
        .unwrap()
        .lines()
        .map(|s| s.trim().parse::<usize>().unwrap())
        .collect::<Vec<_>>();

    let result = fresh
        .iter()
        .filter(|ingredient| {
            for item in &ranges {
                if &&item.start <= ingredient && ingredient <= &&item.end {
                    return true;
                }
            }
            false
        })
        .count();
    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "3-5
10-14
16-20
12-18

1
5
8
11
17
32
";

        assert_eq!(super::solve_part(input).unwrap(), 3);
    }
}
