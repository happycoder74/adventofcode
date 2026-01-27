use aoc_utils::aoc_get_data;
use std::fmt::Display;

#[derive(Debug)]
struct NumberError;

impl Display for NumberError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "NumberError")
    }
}

struct Assignment {
    start: u32,
    end: u32,
}

fn solve_part_1(input: &[(Assignment, Assignment)]) -> Result<usize, NumberError> {
    Ok(input
        .iter()
        .filter(|(a1, a2)| {
            (a1.start <= a2.start && a2.end <= a1.end) || (a2.start <= a1.start && a1.end <= a2.end)
        })
        .count())
}

fn solve_part_2(input: &[(Assignment, Assignment)]) -> Result<usize, String> {
    Ok(input
        .iter()
        .filter(|(a1, a2)| {
            (a1.start <= a2.start && a2.start <= a1.end)
                || (a2.start <= a1.start && a1.start <= a2.end)
        })
        .count())
}

fn parse_input(input: &str) -> Vec<(Assignment, Assignment)> {
    let mut result = vec![];
    for line in input.lines() {
        let (part1, part2) = line.split_once(',').unwrap();
        let (start, end) = part1.split_once('-').unwrap();
        let ass1 = Assignment {
            start: start.parse().unwrap(),
            end: end.parse().unwrap(),
        };
        let (start, end) = part2.split_once('-').unwrap();
        let ass2 = Assignment {
            start: start.parse().unwrap(),
            end: end.parse().unwrap(),
        };

        result.push((ass1, ass2));
    }
    result
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "04");
    let commands = parse_input(&input);

    let start = std::time::Instant::now();
    match solve_part_1(&commands) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&commands) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: &str = "2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8";

    #[test]
    fn test_part_1() {
        let input = parse_input(DATA);
        let result = solve_part_1(&input).unwrap();
        assert_eq!(2, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA);
        let result = solve_part_2(&input).unwrap();
        assert_eq!(4, result);
    }
}
