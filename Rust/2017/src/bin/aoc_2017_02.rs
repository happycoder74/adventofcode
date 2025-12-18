use aoc_utils::{AocError, AocPartReturn, AocResult, AocReturn};
use itertools::Itertools;

fn main() {
    let input = aoc_utils::read_input(2017, 2, false);
    let parsed = parse_input(&input);

    let results = AocReturn::from_parts(solve_part_1(&parsed), solve_part_2(&parsed));
    aoc_utils::report(results);
}

fn parse_input(input: &str) -> Vec<Vec<u32>> {
    input
        .lines()
        .map(|l| {
            l.trim()
                .split_whitespace()
                .map(|n| n.parse().unwrap())
                .collect()
        })
        .collect()
}

fn solve_part_1(input: &[Vec<u32>]) -> Result<AocPartReturn, AocError> {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .map(|v| v.iter().max().unwrap() - v.iter().min().unwrap())
        .sum();
    let end_time = std::time::Instant::now();
    Ok(AocPartReturn {
        result: aoc_utils::AocResult::U32(result),
        duration: end_time - start_time,
    })
}

fn solve_part_2(input: &Vec<Vec<u32>>) -> Result<AocPartReturn, AocError> {
    let start_time = std::time::Instant::now();
    let mut result: u32 = 0;

    for line in input {
        for num in line.iter().permutations(2) {
            if (num[0] % num[1]) == 0 {
                result += num[0] / num[1];
            }
        }
    }
    let end_time = std::time::Instant::now();
    Ok(AocPartReturn {
        result: AocResult::U32(result),
        duration: end_time - start_time,
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1() {
        let input = parse_input(&String::from(
            "5 1 9 5
7 5 3
2 4 6 8
",
        ));

        assert_eq!(18, solve_part_1(&input).unwrap().result.try_into().unwrap());
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(&String::from(
            "5 9 2 8
9 4 7 3
3 8 6 5
",
        ));
        assert_eq!(9, solve_part_2(&input).unwrap().result.try_into().unwrap());
    }
}
