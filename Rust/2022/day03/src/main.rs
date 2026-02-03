use aoc_utils::{AocError, aoc_get_data};

fn prio(input: u8) -> u32 {
    match input {
        b'a'..=b'z' => u32::from(input - b'a' + 1),
        b'A'..=b'Z' => u32::from(input - b'A' + 27),
        _ => unreachable!(),
    }
}

fn parse_input(input: &str) -> Result<Vec<&[u8]>, AocError> {
    let rucksacks = input
        .trim()
        .lines()
        .map(|s| s.as_bytes())
        .collect::<Vec<_>>();

    Ok(rucksacks)
}

fn solve_part_1(input: &[&[u8]]) -> Result<u32, String> {
    let result = input
        .iter()
        .map(|part| {
            let (p1, p2) = (&part[..part.len() / 2], &part[part.len() / 2..]);
            let mut first_array = [0u32; 52];
            let mut second_array = [0u32; 52];
            for (c1, c2) in (p1).into_iter().zip(p2) {
                let (i1, i2) = (prio(*c1) - 1, prio(*c2) - 1);
                first_array[i1 as usize] = 1;
                second_array[i2 as usize] = 1;
            }
            let position = first_array
                .iter()
                .zip(second_array)
                .map(|a| a.0 + a.1)
                .position(|v| v > 1u32)
                .unwrap()
                + 1;
            position
        })
        .sum::<usize>() as u32;
    Ok(result)
}

fn solve_part_2(input: &[&[u8]]) -> Result<usize, String> {
    let result = input
        .chunks(3)
        .map(|c| {
            let mut first_array = [0u32; 52];
            let mut second_array = [0u32; 52];
            let mut third_array = [0u32; 52];
            for c1 in c[0] {
                first_array[(prio(*c1) - 1) as usize] = 1;
            }
            for c2 in c[1] {
                second_array[(prio(*c2) - 1) as usize] = 1;
            }
            for c3 in c[2] {
                third_array[(prio(*c3) - 1) as usize] = 1;
            }
            let position = first_array
                .into_iter()
                .zip(second_array)
                .zip(third_array)
                .map(|((a, b), c)| a + b + c)
                .position(|v| v == 3)
                .expect("Could not find value");
            position + 1
        })
        .sum();
    Ok(result)
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "03");
    let input = parse_input(input).unwrap();

    let start = std::time::Instant::now();
    match solve_part_1(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&input) {
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

    const DATA: &str = "vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw";

    #[test]
    fn test_part_1() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_1(&input).unwrap();
        assert_eq!(157, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!(70, result);
    }
}
