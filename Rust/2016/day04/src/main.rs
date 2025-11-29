use aoc_utils::read_input;
use day04::part1;
use day04::part2;

fn main() {
    if let Ok(input) = read_input(4) {
        let rooms: Vec<_> = input.lines().collect();
        match part1::solve_part(&rooms) {
            Ok(x) => println!("Part 4: {x}"),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
        match part2::solve_part(&rooms) {
            Ok(x) => println!("Part 4: {x}"),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
    } else {
        println!("Could not open input file");
    }
}
