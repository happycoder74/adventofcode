use aoc_utils::read_input;
use day03::part1;
use day03::part2;

fn main() {
    if let Ok(input) = read_input(3) {
        let instructions = part1::parse_input(&input);
        match part1::solve_part(&instructions) {
            Ok(x) => println!("Part 1: {}", x),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
        let instructions = part2::parse_input(&input);
        match part1::solve_part(&instructions) {
            Ok(x) => println!("Part 2: {}", x),
            Err(e) => println!("Part 2: Error {e:?}"),
        }
    } else {
        println!("Could not read input file");
    }
}
