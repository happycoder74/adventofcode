#[macro_export]
#[cfg(windows)]
macro_rules! aoc_get_data {
    ($year:tt, $day:tt) => {
        include_str!(concat!(
            env!("USERPROFILE"),
            "/src/adventofcode/data/",
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

#[cfg(windows)]
macro_rules! aoc_get_bytes{
    ($year:tt, $day:tt) => {
        include_bytes!(concat!(
            env!("USERPROFILE"),
            "/src/adventofcode/data/",
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
