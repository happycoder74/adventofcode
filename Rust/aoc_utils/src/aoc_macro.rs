#![allow(unused)]
#[macro_export]
macro_rules! generate_day {
    () => {
        struct Day {
            input: String,
        }

        impl Day {
            fn new(year: u32, day: u32) -> Self {
                let input = aoc_utils::read_input(year, day, false);
                Self { input }
            }
        }
    };
}

#[macro_export]
#[cfg(windows)]
macro_rules! aoc_get_data {
    ($year:tt, $day:tt) => {
        include_str!(concat!(
            "/Local/msys64/home/yy11510/projects/adventofcode/data/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
    ($year:tt, $day:tt, $path:tt) => {
        include_str!(concat!(
            $path
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
}
#[macro_export]
#[cfg(unix)]
macro_rules! aoc_get_data {
    ($year:tt, $day:tt) => {
        include_str!(concat!(
            env!("AOC_DATA_LOCATION"),
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
    ($year:tt, $day:tt, $path:tt) => {
        include_str!(concat!(
            $path
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
}

#[macro_export]
#[cfg(windows)]
macro_rules! aoc_get_bytes{
    ($year:tt, $day:tt) => {
        include_bytes!(concat!(
            "/Local/msys64/home/yy11510/projects/adventofcode/data/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
    ($year:tt, $day:tt, $path:tt) => {
        include_bytes!(concat!(
            $path
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
}
#[macro_export]
#[cfg(unix)]
macro_rules! aoc_get_bytes{
    ($year:tt, $day:tt) => {
        include_str!(concat!(
            env!("AOC_DATA_LOCATION"),
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
    ($year:tt, $day:tt, $path:tt) => {
        include_str!(concat!(
            $path
            "/",
            $year,
            "/",
            $day,
            "/input.txt"
        ))
    };
}
