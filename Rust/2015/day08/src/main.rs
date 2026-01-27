use aoc_utils::{AocError, AocPartResult, AocResult, AocReturn, Puzzle, generate_day};
use std::time::Instant;

generate_day!();

impl Puzzle<Vec<String>, u32, u32> for Day {
    fn parse_input(input: &str) -> Vec<String> {
        input.lines().map(|line| line.to_string()).collect()
    }

    fn solve_part_1(input: &Vec<String>) -> Result<AocPartResult<u32>, AocError> {
        let start_time = Instant::now();
        let line_count = input.iter().map(|line| {
            let (_, cc) = line
                .chars()
                .fold((false, 0), |(flag, count), c| match (flag, c) {
                    (true, 'x') => (false, count + 3),
                    (true, _) => (false, count + 1),
                    (false, '\\') => (true, count),
                    _ => (false, count),
                });
            cc + 2
        });

        let result = line_count.sum::<u32>();
        Ok(AocPartResult {
            result: AocResult::new(result),
            duration: start_time.elapsed(),
        })
    }

    fn solve_part_2(input: &Vec<String>) -> Result<AocPartResult<u32>, AocError> {
        let start_time = Instant::now();
        let line_count = input.iter().map(|line| {
            line.chars()
                .map(|c| match c {
                    '\\' | '"' => 1,
                    _ => 0,
                })
                .sum::<u32>()
                + 2
        });
        let result = line_count.sum::<u32>();

        Ok(AocPartResult {
            result: AocResult::new(result),
            duration: start_time.elapsed(),
        })
    }

    fn solve_all(self) -> AocReturn<u32, u32> {
        let parsed_input = Self::parse_input(&self.input);
        let part1_result = Self::solve_part_1(&parsed_input);
        let part2_result = Self::solve_part_2(&parsed_input);
        AocReturn::from_parts(part1_result, part2_result)
    }
}

fn main() {
    let day = Day::new(2015, 8);

    let results = day.solve_all();

    aoc_utils::report(results);
}
