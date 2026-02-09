use aoc_utils::aoc_get_data;
use day10::parse_input;
use day10::solve_part_1;
use day10::solve_part_2;

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "10");
    let start = std::time::Instant::now();
    let input = parse_input(input).unwrap();
    println!("Prep time: {:?}", start.elapsed());

    let start = std::time::Instant::now();
    match solve_part_1(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&input) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}
