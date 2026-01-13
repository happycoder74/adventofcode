#![allow(unused_variables)]
use aoc_utils::read_input;
use day12::parse_packages;
use day12::part1;
use std::time::Instant;

fn main() -> anyhow::Result<()> {
    let input = read_input(12)?;

    let field = parse_packages(&input).unwrap();
    let start = Instant::now();
    match part1::solve_part(&field) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part 1: Error '{e}'"),
    }
    // let start = Instant::now();
    // match part2::solve_part(&input) {
    //     Ok(result) => {
    //         let duration = start.elapsed();
    //         println!("Part 2: {result} - {duration:?}");
    //     }
    //     Err(e) => println!("Part 2: Error '{e}'"),
    // }
    Ok(())
}
