use clap::Parser;

macro_rules! either {
    ($test:expr => $true_expr:expr, $false_expr:expr) => {
        match $test {
            true => $true_expr,
            false => $false_expr,
        }
    };
}

#[derive(Parser, Debug)]
#[command(version, about, long_about=None)]
struct Args {
    /// Day to run solution for
    #[arg(short, long)]
    day: u8,

    /// Run test case instead of real input
    #[arg(short, long, default_value_t = false)]
    test: bool,
}

fn main() {
    let args = Args::parse();
    println!(
        "You have selected to run {} for day {:02}",
        either!(args.test => "the test case","the real solution"),
        args.day
    );

    match args.day {
        1 => aoc_2023::aoc_2023_01::run(args.test),
        4 => aoc_2023::aoc_2023_04::run(args.test),
        _ => {
            println!("Day {} is not yet implemented", args.day)
        }
    }
}
