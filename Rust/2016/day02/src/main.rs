use aoc_utils::read_input;
use day02::part1;
use day02::part2;

fn main() {
    let input = read_input(2);
    if let Ok(x) = &input {
        let instructions = day02::parse_input(&x);
        match part1::solve_part(&instructions) {
            Ok(x) => println!("Part 1: {x}"),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
        match part2::solve_part(&instructions) {
            Ok(x) => println!("Part 2: {x}"),
            Err(e) => println!("Part 2: Error {e:?}"),
        }
    } else {
        println!("Could not read input file");
    }

    // if let Ok(x) = input {
    // } else {
    //     println!("Could not read input file");
    // }
}
