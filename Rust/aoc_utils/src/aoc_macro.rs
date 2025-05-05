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
