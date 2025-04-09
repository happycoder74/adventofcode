use std::fs;

fn read_input(filename: &str) -> String {
    fs::read_to_string(filename).unwrap()
}

fn main() {
    let key = "AOC_DATA_LOCATION";
    let aoc_home = std::env::var(key)
        .expect("AOC_DATA_LOCATION is not set. Please set environment variable AOC_DATA_LOCATION");
    let file_path: String = format!("{aoc_home}/2019/01/input.txt");
    let s = read_input(&file_path);
    println!("Part 1: {}", solve_part_1(&s));
    println!("Part 2: {}", solve_part_2(&s));
}

fn solve_part_1(s: &str) -> i64 {
    s.lines()
        .map(|l| l.parse::<i64>().unwrap())
        .map(|i| i / 3 - 2)
        .sum()
}

fn solve_part_2(s: &str) -> i64 {
    s.lines().map(|l| l.parse::<i64>().unwrap()).map(fuel).sum()
}

fn fuel(i: i64) -> i64 {
    let f = i / 3 - 2;
    if f < 0 {
        return 0;
    }
    f + fuel(f)
}
