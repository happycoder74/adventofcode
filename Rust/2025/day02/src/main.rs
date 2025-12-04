use aoc_utils::read_input;
use day02::part1;
use day02::part2;

fn main() {
    let input = read_input(2);

    match input {
        Ok(x) => {
            let start = std::time::Instant::now();
            match part1::solve_part(&x) {
                Ok(result) => {
                    let duration = std::time::Instant::now() - start;
                    println!("Part 1: {result} - {duration:?}");
                }
                Err(e) => println!("Part 1: Error '{e}'"),
            }
            let start = std::time::Instant::now();
            match part2::solve_part(&x) {
                Ok(result) => {
                    let duration = std::time::Instant::now() - start;
                    println!("Part 2: {result} - {duration:?}");
                }
                Err(e) => println!("Part 2: Error '{e}'"),
            }
        }
        Err(e) => println!("{e:?}"),
    }
}
