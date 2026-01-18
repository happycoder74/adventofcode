#[macro_export]
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
