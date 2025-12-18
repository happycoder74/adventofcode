use std::env;
use std::fs;
use std::path::PathBuf;

pub fn read_input(year: u32, day: u32, testcase: bool) -> String {
    let key = "AOC_DATA_LOCATION";
    let aoc_home = env::var(key)
        .expect("AOC_DATA_LOCATION is not set. Please set environment variable AOC_DATA_LOCATION");
    let mut fp = PathBuf::from_iter([
        aoc_home,
        year.to_string(),
        format!("{day:02}"),
        "input.txt".to_string(),
    ]);
    if testcase {
        fp.set_file_name("test_input.txt");
    }

    fs::read_to_string(fp.into_os_string()).expect("Could not open file!")
}
