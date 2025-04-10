use aoc_runner_derive::aoc;
use regex::Regex;

fn solve(input: &str, part2: bool) -> u64 {
    let pattern = Regex::new(r"(mul\((\d{1,3}),(\d{1,3})\)|don\'t\(\)|do\(\))").unwrap();

    let mut enabled: bool = true;
    let mut result: usize = 0;
    for captures in pattern.captures_iter(input) {
        let full = captures.get(0).map_or("", |m| m.as_str());
        if full.starts_with("do()") {
            enabled = true;
        } else if full.starts_with("don't()") {
            enabled = false;
        } else if full.starts_with("mul") {
            if part2 && !enabled {
                continue;
            }
            let v1 = captures.get(2).map_or("", |m| m.as_str()).parse::<usize>().unwrap();
            let v2 = captures.get(3).map_or("", |m| m.as_str()).parse::<usize>().unwrap();
            result += v1 * v2;
        }
    }
    result as u64
}

#[aoc(day3, part1)]
fn part1(input: &str) -> u64 {
    solve(input, false)
}

#[aoc(day3, part2)]
fn part2(input: &str) -> u64 {
    solve(input, true)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_example() {
        let input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
        assert_eq!(part1(input), 161);
    }

    #[test]
    fn part2_example() {
        let input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
        assert_eq!(part2(input), 48);
    }
}
