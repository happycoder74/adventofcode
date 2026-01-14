use day04::part1;
use day04::part2;

fn main() {
    let data = include_str!(concat!(env!("AOC_DATA_LOCATION"), "/2018/04/input.txt"));
    if let Ok(parsed) = day04::parse_data(data) {
        let start = std::time::Instant::now();
        println!("Part 1: {:<20} [{:?}]", part1(&parsed), start.elapsed());
        let start = std::time::Instant::now();
        println!("Part 2: {:<20} [{:?}]", part2(&parsed), start.elapsed());
    }
}
