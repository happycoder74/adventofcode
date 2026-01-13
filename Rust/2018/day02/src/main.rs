use itertools::Itertools;

fn part1(data: &str) -> u32 {
    let result = data
        .lines()
        .map(|s| {
            let mut m = std::collections::HashMap::new();
            for c in s.chars() {
                let count = m.entry(c).or_insert(0);
                *count += 1;
            }
            (
                m.iter().find(|&x| x.1 == &2).is_some(),
                m.iter().find(|&x| x.1 == &3).is_some(),
            )
        })
        .fold((0, 0), |acc, val| {
            (
                match val.0 {
                    true => acc.0 + 1,
                    false => acc.0,
                },
                match val.1 {
                    true => acc.1 + 1,
                    false => acc.1,
                },
            )
        });
    result.0 * result.1
}

fn part2(data: &str) -> String {
    let mut combinations = data
        .lines()
        .combinations(2)
        .map(|a| a[0].chars().zip(a[1].chars()))
        .filter(|b| {
            b.clone()
                .map(|val| match val.0 != val.1 {
                    true => 1,
                    false => 0,
                })
                .sum::<i32>()
                == 1
        });

    combinations
        .next()
        .unwrap()
        .filter(|a| a.0 == a.1)
        .map(|a| a.0)
        .collect::<String>()
}

fn main() {
    let data = include_str!("/home/christian/projects/adventofcode/data/2018/02/input.txt");

    let start = std::time::Instant::now();
    let part1_result = part1(data);
    println!("Part 1: {:<20} [{:?}]", part1_result, start.elapsed());

    let start = std::time::Instant::now();
    let part2_result = part2(data);
    println!("Part 1: {:<20} [{:?}]", part2_result, start.elapsed());
}
