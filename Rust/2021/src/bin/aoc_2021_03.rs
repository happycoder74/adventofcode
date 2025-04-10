use aoc_utils::output::report;
use std::time::Instant;

fn solve_part_1(input: &str) -> (u32, std::time::Duration) {
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

    (
        (gamma * (!gamma & ((1 << width) - 1))),
        Instant::now() - start_time,
    )
}

fn solve_part_2(_input: &str) -> (&str, std::time::Duration) {
    let start_time = Instant::now();
    ("Not implemented", Instant::now() - start_time)
}

fn main() {
    let contents = aoc_utils::read_input(2021, 3, false);
    report("Part 1", solve_part_1(&contents));
    report("Part 2", solve_part_2(&contents));
}

#[cfg(test)]
mod tests {
    use crate::solve_part_1;
    use crate::solve_part_2;

    #[test]
    fn test_part_1() {
        let input = aoc_utils::read_input(2021, 3, true);
        let result = solve_part_1(&input).0;
        assert_eq!(198, result);
    }

    #[test]
    fn test_part_2() {
        let input = aoc_utils::read_input(2021, 3, true);
        assert_eq!(230, solve_part_2(&input).0);
    }
}
