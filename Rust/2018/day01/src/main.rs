use std::{fs, num::ParseIntError};

fn read_data() -> std::io::Result<Vec<String>> {
    let data_location = env!("AOC_DATA_LOCATION");
    let mut path = std::path::PathBuf::new();
    path.push(data_location);
    path.push("2018");
    path.push("01");
    path.push("input.txt");

    let file_content = fs::read_to_string(path)?;
    Ok(file_content.lines().map(str::to_string).collect::<Vec<_>>())
}

fn parse_data(input: &[String]) -> Result<Vec<i32>, ParseIntError> {
    input.iter().map(|s| s.parse::<i32>()).collect()
}

fn part1(input: &[i32]) -> i32 {
    input.iter().sum()
}

fn part2(input: &[i32]) -> i32 {
    let mut frequencies = std::collections::HashSet::new();
    let mut frequency: i32 = 0;

    frequencies.insert(frequency);

    loop {
        for f in input {
            frequency += f;
            if frequencies.contains(&frequency) {
                return frequency;
            }
            frequencies.insert(frequency);
        }
    }
}

fn main() {
    if let Ok(content) = read_data()
        && let Ok(parsed) = parse_data(&content)
    {
        let start = std::time::Instant::now();
        println!("Part1: {:<20} [{:?}]", part1(&parsed), start.elapsed());
        let start = std::time::Instant::now();
        println!("Part2: {:<20} [{:?}]", part2(&parsed), start.elapsed());
    }
}
