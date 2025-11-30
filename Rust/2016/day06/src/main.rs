use aoc_utils::read_input;
use day06::part1;
use day06::part2;

fn main() {
    if let Ok(input) = read_input(6) {
        let lines: Vec<_> = input.lines().collect();
        match part1::solve_part(&lines) {
            Ok(x) => println!("Part 1: {x}"),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
        match part2::solve_part(&lines) {
            Ok(x) => println!("Part 2: {x}"),
            Err(e) => println!("Part 2: Error {e:?}"),
        }
    } else {
        println!("Could not open input file");
    }
}
