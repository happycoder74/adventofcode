use aoc_utils::report;
use aoc_utils::{AocError, AocPartReturn, AocResult, AocReturn};
use std::time::Instant;

fn solve_part_1(input: &str) -> Result<AocPartReturn, AocError> {
    let start_time = Instant::now();
    let width = input.find("\n").unwrap();
    let count = input.len() / (width + 1);

    let gamma = input
        .lines()
        .map(|l| usize::from_str_radix(l, 2).unwrap())
        .fold(vec![0; width], |count, bits| {
            count
                .into_iter()
                .enumerate()
                .map(|(i, n)| n + ((bits & 1 << i) >> i))
                .collect()
        })
        .into_iter()
        .enumerate()
        .map(|(i, b)| ((b >= count / 2) as u32) << i)
        .sum::<u32>();

    let result = gamma * (!gamma & ((1 << width) - 1));
    Ok(AocPartReturn {
        result: AocResult::U32(result),
        duration: Instant::now() - start_time,
    })
}

fn solve_part_2(_input: &str) -> Result<AocPartReturn, AocError> {
    Err(AocError::new("Not implemented"))
}

fn main() {
    let contents = aoc_utils::read_input(2021, 3, false);
    let part1 = solve_part_1(&contents);
    let part2 = solve_part_2(&contents);
    report(AocReturn::from_parts(part1, part2));
}

#[cfg(test)]
mod tests {

    use crate::solve_part_1;
    use crate::solve_part_2;

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2021, 3, true);
        let result = solve_part_1(&input).unwrap().result.try_into().unwrap();
        assert_eq!(198, result);
    }

    #[test]
    fn test_part_2() {
        let input = aoc_utils::read_input(2021, 3, true);
        assert_eq!(
            230,
            solve_part_2(&input).unwrap().result.try_into().unwrap()
        );
    }
}
