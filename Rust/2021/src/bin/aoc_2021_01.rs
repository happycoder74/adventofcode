use aoc_utils::input::get_input;

fn solve_part_1(x: &Vec<usize>) -> usize {
    x.iter().zip(&x[1..]).filter(|(a, b)| b > a).count()
}

fn solve_part_2(x: &Vec<usize>) -> usize {
    x.iter().zip(&x[3..]).filter(|(a, b)| b > a).count()
}

fn main() {
    let contents = get_input(2021, 1, false);
    let x: Vec<usize> = contents.lines().map(|s| s.parse::<usize>().unwrap()).collect();
    println!("Number of elements: {}", solve_part_1(&x));
    println!("Number of elements: {}", solve_part_2(&x));
}
