use aoc_runner_derive::{aoc, aoc_generator};
use counter::Counter;

#[aoc_generator(day1)]
pub fn parse_input(input: &str) -> (Vec<i32>, Vec<i32>) {
    let mut left = vec![];
    let mut right = vec![];

    for line in input.lines() {
        let (l, r) = line.split_once(" ").unwrap();
        left.push(l.trim().parse().unwrap());
        right.push(r.trim().parse().unwrap());
    }

    return (left, right)
}

#[aoc(day1, part1)]
pub fn solve_part_1(parsed: &(Vec<i32>, Vec<i32>)) -> i32 {
    let mut sum: i32 = 0;

    let mut vec0 = parsed.0.clone();
    let mut vec1 = parsed.1.clone();
    vec0.sort();
    vec1.sort();
    for (v1, v2) in std::iter::zip(vec0, vec1) {
        sum += (v1 - v2).abs();
    }

    let counts = parsed.0.iter().collect::<Counter<_>>();
    println!("{:?}", counts);
    sum
}


#[cfg(test)]
mod tests {
    use super::*;

    const INPUT: &str = " 3   4
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
}
