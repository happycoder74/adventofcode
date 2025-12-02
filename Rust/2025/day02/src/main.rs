use aoc_utils::read_input;
use day02::part1;
use day02::part2;

fn main() {
    let input = read_input(2);

    match input {
        Ok(x) => {
            match part1::solve_part(&x) {
                Ok(result) => println!("Part 1: {result}"),
                Err(e) => println!("Part 1: Error '{e}'"),
            }
            match part2::solve_part(&x) {
                Ok(result) => println!("Part 2: {result}"),
                Err(e) => println!("Part 2: Error '{e}'"),
            }
        }
        Err(e) => println!("{e:?}"),
    }
}
