use aoc_utils::aoc_get_data;
use day06::{calc_grid_size, parse, part1, part2};

fn main() {
    let input = aoc_get_data!("2018", "06");
    if let Ok(parsed) = parse(input)
        && let Ok(grid_size) = calc_grid_size(&parsed)
    {
        let start = std::time::Instant::now();
        if let Ok(result) = part1(&parsed, &grid_size) {
            println!("Part 1: {:<20} [{:?}]", result, start.elapsed());
        } else {
            eprintln!("Error in part 1");
        }

        let start = std::time::Instant::now();
        if let Ok(result) = part2(&parsed, &grid_size, 10000) {
            println!("Part 2: {:<20} [{:?}]", result, start.elapsed());
        } else {
            eprintln!("Error in part 2");
        }
    }
}
