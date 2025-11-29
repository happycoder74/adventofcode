use aoc_utils::{AocError, AocPartReturn, AocResult, AocReturn};

fn solve_part_1(x: &[usize]) -> Result<AocPartReturn, AocError> {
    let start_time = std::time::Instant::now();
    let result = x.iter().zip(&x[1..]).filter(|(a, b)| b > a).count();
    let end_time = std::time::Instant::now();
    Ok(AocPartReturn {
        result: AocResult::Usize(result),
        duration: end_time - start_time,
    })
}

fn solve_part_2(x: &[usize]) -> Result<AocPartReturn, AocError> {
    let start_time = std::time::Instant::now();
    let result = x.iter().zip(&x[3..]).filter(|(a, b)| b > a).count();
    let end_time = std::time::Instant::now();
    Ok(AocPartReturn {
        result: AocResult::Usize(result),
        duration: end_time - start_time,
    })
}

fn main() {
    let contents = aoc_utils::read_input(2021, 1, false);
    let x: Vec<usize> = contents
        .lines()
        .map(|s| s.parse::<usize>().unwrap())
        .collect();
    let part1 = solve_part_1(&x);
    let part2 = solve_part_2(&x);
    let result = AocReturn::from_parts(part1, part2);
    aoc_utils::report(result);
}
