use aoc_utils::aoc_get_data;
use day04::part1;
use day04::part2;

fn main() {
    let data = aoc_get_data!("2018", "04");
    if let Ok(parsed) = day04::parse_data(data) {
        let start = std::time::Instant::now();
        println!("Part 1: {:<20} [{:?}]", part1(&parsed), start.elapsed());
        let start = std::time::Instant::now();
        println!("Part 2: {:<20} [{:?}]", part2(&parsed), start.elapsed());
    }
}
