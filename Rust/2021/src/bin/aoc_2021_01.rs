fn solve_part_1(x: &Vec<usize>) -> (usize, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = x.iter().zip(&x[1..]).filter(|(a, b)| b > a).count();
    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}

fn solve_part_2(x: &Vec<usize>) -> (usize, std::time::Duration) {
    let start_time = std::time::Instant::now();
    let result = x.iter().zip(&x[3..]).filter(|(a, b)| b > a).count();
    let end_time = std::time::Instant::now();
    (result, end_time - start_time)
}

fn main() {
    let contents = aoc_utils::read_input(2021, 1, false);
    let x: Vec<usize> = contents.lines().map(|s| s.parse::<usize>().unwrap()).collect();
    aoc_utils::report("Part 1", solve_part_1(&x));
    aoc_utils::report("Part 2", solve_part_2(&x));
}
