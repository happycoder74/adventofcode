use aoc_utils::aoc_get_data;
use std::{collections::VecDeque, error::Error, fmt::Display};

#[derive(Debug)]
enum AocError {
    NotImplementedError,
    InputError,
    StackIndexError,
    EmptyStack,
    SolutionNotFound,
}

impl Error for AocError {}

impl Display for AocError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::NotImplementedError => write!(f, "NotImplementedError"),
            Self::InputError => write!(f, "Input error"),
            Self::EmptyStack => write!(f, "Empty stack"),
            Self::StackIndexError => write!(f, "Stack Index Error"),
            Self::SolutionNotFound => write!(f, "Solution not found"),
        }
    }
}

fn find_unique(win: &[u8], size: usize) -> bool {
    for i in 0..(size - 1) {
        for j in (i + 1)..size {
            if win[i] == win[j] {
                return false;
            }
        }
    }

    return true;
}

fn solver(input: &str, size: usize) -> Result<usize, Box<dyn Error>> {
    let input_bytes = input.trim().as_bytes();

    let mut iter = input_bytes.windows(size).enumerate();

    while let Some((i, win)) = iter.next() {
        if find_unique(win, size) {
            return Ok(i + size);
        }
    }
    Err(AocError::SolutionNotFound.into())
}

fn solve_part_1(input: &str) -> Result<usize, Box<dyn Error>> {
    solver(input, 4)
}

fn solve_part_2(input: &str) -> Result<usize, Box<dyn Error>> {
    solver(input, 14)
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "06");

    let start = std::time::Instant::now();
    match solve_part_1(input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: [&str; 5] = [
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
        "bvwbjplbgvbhsrlpgdmjqwftvncz",
        "nppdvjthqldpwncqszvftbrmjlhg",
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",
    ];

    #[test]
    fn test_part_1() {
        assert_eq!(7, solve_part_1(DATA[0]).unwrap());
        assert_eq!(5, solve_part_1(DATA[1]).unwrap());
        assert_eq!(6, solve_part_1(DATA[2]).unwrap());
        assert_eq!(10, solve_part_1(DATA[3]).unwrap());
        assert_eq!(11, solve_part_1(DATA[4]).unwrap());
    }

    #[test]
    fn test_part_2() {
        assert_eq!(19, solve_part_2(DATA[0]).unwrap());
        assert_eq!(23, solve_part_2(DATA[1]).unwrap());
        assert_eq!(23, solve_part_2(DATA[2]).unwrap());
        assert_eq!(29, solve_part_2(DATA[3]).unwrap());
        assert_eq!(26, solve_part_2(DATA[4]).unwrap());
    }
}
