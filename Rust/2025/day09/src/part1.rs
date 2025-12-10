#![allow(unused_variables)]
use aoc_utils::Location;
use aoc_utils::NotImplementedError;
use itertools::Itertools;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let result = input
        .lines()
        .map(|line| line.trim().parse::<Location<usize>>().unwrap())
        .combinations(2)
        .map(|v| {
            let l1 = &v[0];
            let l2 = &v[1];
            (l1.x.abs_diff(l2.x) + 1) * (l1.y.abs_diff(l2.y) + 1)
        })
        .max()
        .unwrap();

    Ok(result)
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

        assert_eq!(super::solve_part(input).unwrap(), 50);
    }
}
