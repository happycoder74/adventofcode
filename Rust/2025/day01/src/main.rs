use aoc_utils::read_input;
use day01::part1;
use day01::part2;

fn main() {
    let input = read_input(1);

    match input {
        Ok(x) => {
            let commands = x.lines().map(str::trim).collect();
            let start = std::time::Instant::now();
            match part1::solve_part(&commands) {
                Ok(result) => {
                    let duration = std::time::Instant::now() - start;
                    println!("Part 1: {result} - {duration:?}");
                }
                Err(e) => println!("Part1: Error '{e:?}'"),
            }
            let start = std::time::Instant::now();
            match part2::solve_part(&commands) {
                Ok(result) => {
                    let duration = std::time::Instant::now() - start;
                    println!("Part 2: {result} - {duration:?}");
                }
                Err(e) => println!("Part2: Error '{e:?}'"),
            }
        }
        Err(e) => println!("{e:?}"),
    }
}
