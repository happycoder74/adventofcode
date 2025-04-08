use aoc_utils::*;

pub fn parse_input(input: &str) -> Vec<(u32, u32, u32)>{
    input
        .lines()
        .map(|l| l.trim())
        .filter(|l| !l.is_empty())
        .map(|l| {
            let mut numbers = l
                .split("x")
                .map(|v| v.parse::<u32>().unwrap())
                .collect::<Vec<_>>();
            numbers.sort_unstable();
            (numbers[0], numbers[1], numbers[2])
        })
        .collect()
}

pub fn solve_part_1(input: &Vec<(u32, u32, u32)>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .fold(0, |s, (l, w, h)| {
            2 * (l * w + w * h + h * l) + l*w + s
        });
    let duration = std::time::Instant::now() - start_time;

    (result, duration)
}

pub fn solve_part_2(input: &Vec<(u32, u32, u32)>) -> (u32, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = input
        .iter()
        .map(|(l, w, h)| {
            2 * (l + w ) + (l * w * h)
        }).sum();
    let duration = std::time::Instant::now() - start_time;

    (result, duration)
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
