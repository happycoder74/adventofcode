use aoc_runner_derive::{aoc, aoc_generator};

#[aoc_generator(day1)]
pub fn parse_input(input: &str) -> (Vec<usize>, Vec<usize>) {
    let mut left = vec![];
    let mut right = vec![];

    for line in input.lines() {
        let l: Vec<&str> = line.split(" ").collect();
        left.push(l.first().unwrap().parse().unwrap());
        right.push(l.last().unwrap().parse().unwrap());
    }

    return (left, right)
}

#[aoc(day1, part1)]
pub fn solve_part_1(parsed: &(Vec<usize>, Vec<usize>)) -> usize {
    let mut vec0 = parsed.0.clone();
    let mut vec1 = parsed.1.clone();
    vec0.sort();
    vec1.sort();

    sum
}

#[aoc(day1, part2)]
pub fn solve_part_2(parsed: &(Vec<i32>, Vec<i32>)) -> i32 {
    let mut sum: i32 = 0;

    for v1 in &parsed.0 {
        sum += v1 * (parsed.1.iter().filter(|n| *n == v1).count()) as i32;
    }

    sum
}


#[cfg(test)]
mod tests {
    use super::*;

    const INPUT: &str = "3   4
4   3
2   5
1   3
3   9
3   3";

    #[test]
    fn part_1_test() {
        let parsed = parse_input(INPUT);

        assert_eq!(solve_part_1(&parsed), 11);
    }

    #[test]
    fn part_2_test() {
        let parsed = parse_input(INPUT);

        assert_eq!(solve_part_2(&parsed), 31);
    }
}
