use aoc_utils::*;

pub fn parse_input(input: &str) -> Vec<(u32, u32, u32)>{
    input
        .lines()
        .map(|l| l.trim())
        .filter(|l| !l.is_empty())
        .map(|l| {
            let numbers = l
                .split("x")
                .map(|v| v.parse::<u32>().unwrap())
                .collect::<Vec<_>>();
            (numbers[0], numbers[1], numbers[2])
        })
        .collect()
}

pub fn solve_part_1(input: &Vec<(u32, u32, u32)>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .fold(0, |s, dims| {
            let side1 = dims.0 * dims.1;
            let side2 = dims.1 * dims.2;
            let side3 = dims.2 * dims.0;
            2 * side1 + 2 * side2 + 2 * side3 + std::cmp::min(std::cmp::min(side1, side2), side3) + s
        });
    let end_time = std::time::Instant::now();

    (result, end_time - start_time)
}

pub fn solve_part_2(input: &Vec<(u32, u32, u32)>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .fold(0, |s, dims| {
            2 * std::cmp::min(dims.0, dims.1) + 2 * std::cmp::min(dims.1, dims.2) + dims.0 * dims.1 * dims.2 + s
        });

    (result, std::time::Instant::now() - start_time)
}

fn solve_all() -> ((u32, std::time::Duration), (u32, std::time::Duration)) {
    let input = get_input(2015, 2, false);
    let parsed = parse_input(&input);

    (solve_part_1(&parsed), solve_part_2(&parsed))
}

fn main() {
    let result = solve_all();
    report ("Part1", result.0);
    report ("Part2", result.1);
}

#[cfg(test)]
mod tests {
    use crate::{parse_input, solve_part_1, solve_part_2};

    #[test]
    fn test_part_1() {
        let input = "2x3x4\n1x1x10";
        let parsed = parse_input(&input);
        assert_eq!(101, solve_part_1(&parsed).0);
    }

    #[test]
    fn test_part_2() {
        let input = "2x3x4
1x1x10
";
        let parsed = parse_input(&input);
        assert_eq!(14 + 34, solve_part_2(&parsed).0);
    }
}
