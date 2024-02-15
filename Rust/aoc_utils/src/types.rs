use std::time::Duration;

pub struct AocReturn {
    pub result: i32,
    pub duration: Duration
}

pub trait Puzzle<T, U> {
    fn get_input(year: u32, day: u32, testcase: bool) -> String;
    fn parse_input(input: &str) -> T;
    fn solve_part_1(input: &T) -> U;
    fn solve_part_2(input: &T) -> U;
    fn solve_all(self) -> (U, U);
}
