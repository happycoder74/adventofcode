#![allow(unused_variables)]

use aoc_utils::NotImplementedError;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, Box<dyn std::error::Error>> {
    Err(Box::new(NotImplementedError))
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "0:
###
##.
##.

1:
###
##.
.##

2:
.##
###
##.

3:
##.
###
##.

4:
###
#..
###

5:
###
.#.
###

4x4: 0 0 0 0 2 0
12x5: 1 0 1 0 2 2
12x5: 1 0 1 0 3 2";

        assert_eq!(super::solve_part(input).unwrap(), 2);
    }
}
