#![allow(unused_variables)]

use std::iter::zip;

use anyhow::Result;
use aoc_utils::NotImplementedError;

use crate::{Package, PlayingField, parse_packages, print_grid};

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(field: &PlayingField) -> Result<usize> {
    let packages = &field.packages;
    let regions = &field.regions;

    let result = regions
        .iter()
        .filter(|region| {
            let field_size = region.area;
            let package_size = region.packages.iter().sum::<i32>() * 9i32;

            field_size >= package_size
        })
        .count();

    Ok(result)
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

        let field = crate::parse_packages(input).unwrap();
        assert_eq!(super::solve_part(&field).unwrap(), 2);
    }
}
