use itertools::Itertools;

fn main() {
    let input = aoc_utils::read_input(2017, 2, false);
    let parsed = parse_input(&input);

    aoc_utils::report("Part 1", solve_part_1(&parsed));
    aoc_utils::report("Part 2", solve_part_2(&parsed));
}

fn parse_input(input: &str) -> Vec<Vec<u32>> {
    input
        .lines()
        .map(|l| l
            .trim()
            .split_whitespace()
            .map(|n| n.parse().unwrap())
            .collect()
            )
        .collect()
}


fn solve_part_1(input: &Vec<Vec<u32>>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .map(|v| v.iter().max().unwrap() - v.iter().min().unwrap())
        .sum();
    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}

fn solve_part_2(input: &Vec<Vec<u32>>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let mut result: u32 = 0;

    for line in input {
        for num in line.iter().permutations(2) {
            match (num[0] % num[1]) == 0 {
                    true => result += num[0] / num[1],
                    false => ()
            }
        }
    }
    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}


#[cfg(test)]
mod tests{
    use super::*;

    #[test]
    fn test_part_1() {
        let input = parse_input(&String::from("5 1 9 5
7 5 3
2 4 6 8
"));

        assert_eq!(18, solve_part_1(&input).0);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(&String::from("5 9 2 8
9 4 7 3
3 8 6 5
"));
        assert_eq!(9, solve_part_2(&input).0);
    }
}

