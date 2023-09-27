use std::fs;

fn parse_input(year: u32, day: u32) -> String {
    let file_path = format!("/home/yy11510/projects/adventofcode/data/{year}/{day:02}/input.txt");
    let contents = fs::read_to_string(file_path);
    return contents.unwrap();
}

fn solve_part_1(x: &Vec<usize>) -> usize {
    x.iter().zip(&x[1..]).filter(|(a, b)| b > a).count()
}

fn solve_part_2(x: &Vec<usize>) -> usize {
    x.iter().zip(&x[3..]).filter(|(a, b)| b > a).count()
}

fn main() {
    let contents = parse_input(2021, 1);
    let x: Vec<usize> = contents.lines().map(|s| s.parse::<usize>().unwrap()).collect();

    println!("Number of elements: {}", solve_part_1(&x));
    println!("Number of elements: {}", solve_part_2(&x));
}
