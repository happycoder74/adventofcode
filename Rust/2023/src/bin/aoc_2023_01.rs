use aoc_utils::report;
use aoc_utils::AocError;
use aoc_utils::AocPartReturn;
use aoc_utils::AocResult;
use aoc_utils::AocReturn;
use std::collections::HashMap;
use std::time::Instant;

#[allow(clippy::search_is_some)]
fn get_numbers(input: &str, digit_map: &HashMap<&str, i32>) -> (i32, i32) {
    let res_first: Vec<_> = digit_map
        .iter()
        .filter(|(k, _)| (input.find(*k).is_some()))
        .map(|(k, v)| {
            let value = input.find(k);
            match value {
                Some(x) => x as i32,
                None => -1,
            };
            (value, v)
        })
        .collect();

    let res_last: Vec<_> = digit_map
        .iter()
        .filter(|(k, _)| (input.rfind(*k).is_some()))
        .map(|(k, v)| (input.rfind(k).unwrap(), v))
        .collect();

    (
        *res_first.iter().min_by_key(|x| x.0).unwrap().1,
        *res_last.iter().max_by_key(|x| x.0).unwrap().1,
    )
}

fn solve_part_1(input: &str) -> Result<AocPartReturn, AocError> {
    let start_time = Instant::now();
    let map = HashMap::from_iter([
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
    ]);
    let result: i32 = input
        .lines()
        .map(|line| get_numbers(line, &map))
        .map(|(f, l)| f * 10 + l)
        .sum();
    Ok(AocPartReturn {
        result: AocResult::U32(result as u32),
        duration: Instant::now() - start_time,
    })
}

fn solve_part_2(input: &str) -> Result<AocPartReturn, AocError> {
    let map_p2: HashMap<&str, i32> = HashMap::from_iter([
        ("1", 1),
        ("2", 2),
        ("3", 3),
        ("4", 4),
        ("5", 5),
        ("6", 6),
        ("7", 7),
        ("8", 8),
        ("9", 9),
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ]);
    let start_time = Instant::now();
    let result: i32 = input
        .lines()
        // .map(|line| get_numbers(line, &map_p2))
        .map(|line| get_numbers(line, &map_p2))
        .map(|(f, l)| f * 10 + l)
        .sum();
    Ok(AocPartReturn {
        result: AocResult::U32(result as u32),
        duration: Instant::now() - start_time,
    })
}

pub fn main() {
    let input = aoc_utils::read_input(2023, 1, false);
    report(AocReturn::from_parts(
        solve_part_1(&input),
        solve_part_2(&input),
    ));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2023, 4, true);
        assert_eq!(142u32, solve_part_1(&input).unwrap().result.into())
    }
}
