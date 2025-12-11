#![allow(unused_variables)]
use aoc_utils::NotImplementedError;

use crate::parse_input;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, Box<dyn std::error::Error>> {
    if let Ok(instructions) = parse_input(input) {
        let mut to_visit = vec![];
        to_visit.push("svr".to_string());
        let mut paths = 0usize;
        while let Some(node) = to_visit.pop() {
            if let Some(destinations) = instructions.get(&node) {
                for destination in destinations {
                    if destination == "dac" {
                        paths += 1;
                    } else {
                        to_visit.push(destination.clone());
                    }
                }
            }
        }
        return Ok(paths);
    }
    Err(Box::new(NotImplementedError))
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out";

        assert_eq!(super::solve_part(input).unwrap(), 0);
    }
}
