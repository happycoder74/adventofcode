mod part1;
mod part2;

fn main() {
    let input = day01::read_input();
    if let Ok(x) = input {
        match part1::solve_part(&x) {
            Ok(x) => println!("Part 1: {x}"),
            Err(e) => println!("Part 1: Error {e:?}"),
        }
    } else {
        println!("Could not read input file");
    }

    let input = day01::read_input();
    if let Ok(x) = input {
        match part2::solve_part(&x) {
            Ok(x) => println!("Part 2: {x}"),
            Err(e) => println!("Part 2: Error {e:?}"),
        }
    } else {
        println!("Could not read input file");
    }
}
