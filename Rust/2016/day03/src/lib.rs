pub mod part1;
pub mod part2;

pub fn is_triangle(candidate: &Vec<u32>) -> bool {
    candidate[0] + candidate[1] > candidate[2]
        && candidate[1] + candidate[2] > candidate[0]
        && candidate[2] + candidate[0] > candidate[1]
}
