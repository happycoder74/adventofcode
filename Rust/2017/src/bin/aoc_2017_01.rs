fn main() {
    let input = aoc_utils::read_input(2017, 1, false);
    let parsed = parse_input(&input);

    println!("Part 1: {}", solve_part_1(&parsed));
    println!("Part 2: {}", solve_part_2(&parsed));
}

fn parse_input(input: &str) -> Vec<u32> {
    // input
    //     .chars()
    //     .filter(|c| char::is_digit(*c, 10))
    //     .map(|c| c.to_digit(10).unwrap())
    //     .collect()
    input.trim().split("").filter(|l| !l.is_empty()).map(|l| l.parse().unwrap()).collect()
}

fn solver(input: &[u32], skip: usize) -> u32 {
    input
        .iter()
        .skip(skip)
        .chain(input.iter().take(skip))
        .zip(input)
        .filter(|(s1, s2)| s1 == s2)
        .map(|c| c.0)
        .sum()
}

fn solve_part_1(input: &[u32]) -> u32 {
    solver(input, 1)
}

fn solve_part_2(input: &[u32]) -> u32 {
    solver(input, input.len() / 2)
}

#[cfg(test)]
mod tests{
    use super::*;

    #[test]
    fn test_part_1() {
        let input = parse_input(&String::from("91212129"));

        assert_eq!(9, solve_part_1(&input));
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(&String::from("12131415"));

        assert_eq!(4, solve_part_2(&input));
    }
}
