#![allow(unused_variables)]

use aoc_utils::NotImplementedError;

use crate::parse_input;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, Box<dyn std::error::Error>> {
    if let Ok(instructions) = parse_input(input) {
        let mut to_visit = vec![];
        to_visit.push("you".to_string());

        let mut paths = 0usize;
        while let Some(node) = to_visit.pop() {
            if let Some(destinations) = instructions.get(&node) {
                for destination in destinations {
                    if destination == "out" {
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
        let input = "aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out";

        assert_eq!(super::solve_part(input).unwrap(), 5);
    }
}
