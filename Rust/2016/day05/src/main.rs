use aoc_utils::read_input;
use day05::part1;
use day05::part2;

fn main() {
    if let Ok(input) = read_input(5) {
        match part1::solve_part(&input.trim()) {
            Ok(x) => println!("Part 1: {x}"),
            Err(_) => (),
        }
        match part2::solve_part(&input.trim()) {
            Ok(x) => println!("Part 2: {x}"),
            Err(_) => (),
        }
    } else {
        println!("Could not open input file");
    }
}
