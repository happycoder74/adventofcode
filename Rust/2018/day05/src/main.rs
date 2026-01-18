use aoc_utils::aoc_get_data;
use day05::part1;
use day05::part2;

fn main() {
    let data = aoc_get_data!("2018", "05");

    let start = std::time::Instant::now();
    println!("Part 1: {:<20} [{:?}]", part1(data.trim()), start.elapsed());
    let start = std::time::Instant::now();
    println!("Part 2: {:<20} [{:?}]", part2(data.trim()), start.elapsed());
}
