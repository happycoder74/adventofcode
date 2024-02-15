use std::time::Instant;
use aoc_utils::output::report;
use aoc_utils::types::AocReturn;
use aoc_utils::input::get_input;

struct Commands {
    forward: i32,
    down: i32,
    up: i32
}

fn solve_part_1(x: &str) -> AocReturn {
    let start_time = Instant::now();
    let mut commands = Commands{forward: 0, down: 0, up: 0};

    for line in x.lines() {
        let parts = line.split_once(" ").unwrap();
        let value: i32 = parts.1.parse().unwrap();
        match parts.0 {
            "forward" => commands.forward += value,
            "down" => commands.down += value,
            "up" => commands.up += value,
            _ => ()
        }
    }

    AocReturn {result: commands.forward * (commands.down - commands.up), duration: Instant::now() - start_time}
}

fn solve_part_2(input: &str) -> AocReturn {
    let start_time = Instant::now();
    let mut horizontal = 0;
    let mut aim = 0;
    let mut depth = 0;

    for line in input.lines() {
        let parts = line.split_once(" ").unwrap();
        let value: i32 = parts.1.parse().unwrap();
        match parts.0 {
            "forward" => {
                horizontal += value;
                depth += aim * value;
            },
            "down" => aim += value,
            "up" => aim -= value,
            _ => ()
        }
    }
    AocReturn {
        result: horizontal * depth,
        duration: Instant::now() - start_time
    }
}

fn main() {
    let contents = get_input(2021, 2, false);
    report("Part 1", solve_part_1(&contents));
    report("Part 2", solve_part_2(&contents));
}

#[cfg(test)]
mod tests {
    use crate::solve_part_1;
    use crate::solve_part_2;
    fn get_input() -> &'static str {
"forward 5
down 5
forward 8
up 3
down 8
forward 2
"
    }

    #[test]
    fn test_part_1() {
        let input = get_input();
        assert_eq!(150, solve_part_1(&input).result);
    }

    #[test]
    fn test_part_2() {
        let input = get_input();
        assert_eq!(900, solve_part_2(&input).result);
    }
}
