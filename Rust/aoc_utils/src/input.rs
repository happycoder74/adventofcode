use std::env;
use std::fs;

pub fn get_input(year: u32, day: u32, testcase: bool) -> String {
    let key = "AOC_DATA_LOCATION";
    let aoc_home = env::var(key)
        .expect("AOC_DATA_LOCATION is not set. Please set environment variable AOC_DATA_LOCATION");
    let file_path: String;
    if testcase {
        file_path = format!("{aoc_home}/{year}/{day:02}/test_input.txt");
    } else {
        file_path = format!("{aoc_home}/{year}/{day:02}/input.txt");
    }
    let contents = fs::read_to_string(file_path).expect("Could not open file!");
    return contents;
}

