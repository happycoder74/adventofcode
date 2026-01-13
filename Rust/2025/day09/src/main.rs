#![allow(unused_variables)]
use aoc_utils::read_input;
use day09::part1;
use day09::part2;
use std::time::Instant;

fn main() {
    let input = read_input(9);

    match input {
        Ok(x) => {
            let start = Instant::now();
            match part1::solve_part(&x) {
                Ok(result) => {
                    let duration = start.elapsed();
                    println!("Part 1: {result} - {duration:?}");
                }
                Err(e) => println!("Part 1: Error '{e}'"),
            }
            let start = Instant::now();
            match part2::solve_part(&x) {
                Ok(result) => {
                    let duration = start.elapsed();
                    println!("Part 2: {result} - {duration:?}");
                }
                Err(e) => println!("Part 2: Error '{e}'"),
            }
        }
        Err(e) => println!("{e:?}"),
    }
}
