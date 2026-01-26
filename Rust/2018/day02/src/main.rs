use anyhow::Result;

use aoc_utils::aoc_get_data;
use itertools::Itertools;

fn part1(data: &str) -> Result<u32> {
    let letter_count = data
        .lines()
        .map(str::as_bytes)
        .map(|arr| {
            let char_array = &mut [0; 30];
            arr.iter().for_each(|b| {
                let ind = usize::from(b - b'a');
                char_array[ind] += 1
            });
            (
                arr.iter().any(|x| char_array[usize::from(x - b'a')] == 2),
                arr.iter().any(|x| char_array[usize::from(x - b'a')] == 3),
            )
        })
        .fold((0, 0), |acc, val| {
            (
                if val.0 { acc.0 + 1 } else { acc.0 },
                if val.1 { acc.1 + 1 } else { acc.1 },
            )
        });

    Ok(letter_count.0 * letter_count.1)
}

fn part2(data: &str) -> Result<String> {
    let result = data
        .lines()
        .combinations(2)
        .map(|a| a[0].chars().zip(a[1].chars()))
        .filter(|b| b.clone().map(|val| i32::from(val.0 != val.1)).sum::<i32>() == 1)
        .next()
        .unwrap()
        .filter(|a| a.0 == a.1)
        .map(|a| a.0)
        .collect::<String>();

    Ok(result)
}

fn main() {
    let data = aoc_get_data!("2018", "02");

    let start = std::time::Instant::now();
    if let Ok(part1_result) = part1(data) {
        println!("Part 1: {:<20} [{:?}]", part1_result, start.elapsed());
    }

    let start = std::time::Instant::now();
    if let Ok(part2_result) = part2(data) {
        println!("Part 1: {:<20} [{:?}]", part2_result, start.elapsed());
    }
}
