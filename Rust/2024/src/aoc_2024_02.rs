#[aoc_runner_derive::aoc_generator(day2)]
pub fn parse_input(input: &str) -> Vec<Vec<u32>> {
    let return_vector = input
        .lines()
        .map(|line| {
            line.split(' ')
                .map(|num| num.parse::<u32>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect();
    return_vector
}

fn check_step(item: &Vec<u32>) -> bool {
    let zipped: Vec<_> = item
        .iter()
        .zip(&item[1..])
        .collect();
    for a in zipped {
        if (a.0 == a.1) || a.0.abs_diff(*a.1) > 3 {
            return false;
        }
    }
    true
}

fn validate(item: &Vec<u32>) -> bool {
    let mut item2 = item.clone();
    item2.reverse();

    return (item.is_sorted() || item2.is_sorted()) && check_step(item);
}

#[aoc_runner_derive::aoc(day2, part1)]
pub fn solve_part_1(parsed: &Vec<Vec<u32>>) -> usize {
    let sum: Vec<_> = parsed.into_iter().filter(|item| validate(item)).collect();

    sum.into_iter().count()
}

#[aoc_runner_derive::aoc(day2, part2)]
pub fn solve_part_2(parsed: &Vec<Vec<u32>>) -> u32 {
    parsed
        .iter()
        .filter(|item| {
            validate(item)
                || (0..item.len()).any(|i| {
                    let mut values: Vec<u32> = item.to_vec();
                    values.remove(i);
                    validate(&values)
                })
        })
        .count() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    const SAMPLE: &str = "7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9 ";

    #[test]
    pub fn part1_example() {
        let parsed = parse_input(SAMPLE);
        assert_eq!(solve_part_1(&parsed), 2);
    }

    #[test]
    pub fn part2_example() {
        let parsed = parse_input(SAMPLE);
        assert_eq!(solve_part_2(&parsed), 4);
    }
}
