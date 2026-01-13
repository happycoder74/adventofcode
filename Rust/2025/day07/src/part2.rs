#![allow(unused_variables)]
use aoc_utils::NotImplementedError;
use std::collections::HashMap;

// With inspiration taken from prositen/advent-of-code

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let lines = input.lines().map(str::trim).collect::<Vec<_>>();
    let start = lines[0].find('S').unwrap();
    let mut beams = HashMap::new();
    beams.insert(start, 1usize);
    for line in lines {
        let mut new_beams = HashMap::new();
        for (beam, count) in &mut beams {
            if line.chars().nth(*beam).unwrap() == '.' {
                *new_beams.entry(*beam).or_insert(0) += *count;
            } else {
                if *beam > 0 {
                    *new_beams.entry(*beam - 1).or_insert(0) += *count;
                }
                if *beam < line.len() - 1 {
                    *new_beams.entry(*beam + 1).or_insert(0) += *count;
                }
            }
        }
        beams = new_beams;
    }
    let result = beams.iter().fold(0, |acc, (_, v)| acc + v);
    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = ".......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............";

        assert_eq!(super::solve_part(input).unwrap(), 40);
    }
}
