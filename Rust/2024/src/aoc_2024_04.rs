use aoc_runner_derive::{aoc, aoc_generator};

#[aoc_generator(day4)]
pub fn parse(input: &str) -> Vec<String> {
    let lines: Vec<String> = input.lines().map(|m| String::from(m)).collect();
    lines
}

#[aoc(day4, part1)]
pub fn part1(input: &Vec<String>) -> usize {
    let mut result: usize = 0;
    let rows = input.len() as usize;
    let cols = input[0].len() as usize;
    for (row_index, row) in input.iter().enumerate() {
        for (col_index, col) in row.char_indices() {
            if col != 'X' {
                continue;
            }
            for dr in -1..=1 {
                for dc in -1..=1 {
                    if dr == 0 && dc == 0 {
                        continue;
                    }
                    if (row_index as i64 + 3 * dr) < 0 || rows <= (row_index as i64 + 3 * dr) as usize {
                        continue;
                    }
                    if (col_index as i64 + 3 * dc) < 0 || cols <= (col_index as i64 + 3 * dc) as usize {
                        continue;
                    }
                    let ir1: i64 = row_index as i64 + dr;
                    let ic1: i64 = col_index as i64 + dc;
                    if input[ir1 as usize].chars().nth(ic1 as usize).unwrap() == 'M'
                        && input[(ir1 + dr) as usize]
                            .chars()
                            .nth((ic1 + dc) as usize)
                            .unwrap()
                            == 'A'
                        && input[(ir1 + 2 * dr) as usize]
                            .chars()
                            .nth((ic1 + 2 * dc) as usize)
                            .unwrap()
                            == 'S'
                    {
                        result += 1;
                    }
                }
            }
        }
    }
    result
}

#[aoc(day4, part2)]
pub fn part2(input: &Vec<String>) -> u64 {
    let mut result: u64 = 0;
    let rows = input.len();
    let cols = input[0].len();
    for (row_index, row) in input.iter().enumerate() {
        for (col_index, col) in row.char_indices() {
            if row_index == 0 || row_index == rows - 1 || col_index == 0 || col_index == cols - 1 {
                continue;
            }
            if col != 'A' {
                continue;
            }
            let ul = input[row_index - 1].chars().nth(col_index - 1).unwrap();
            let dl = input[row_index + 1].chars().nth(col_index - 1).unwrap();
            let ur = input[row_index - 1].chars().nth(col_index + 1).unwrap();
            let dr = input[row_index + 1].chars().nth(col_index + 1).unwrap();
            let ulx = ul as u8;
            let dlx = dl as u8;
            let urx = ur as u8;
            let drx = dr as u8;

            if ulx.abs_diff(drx) == 6 && urx.abs_diff(dlx) == 6 {
                result += 1;
            }
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    const SAMPLE: &str = "MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX";

    #[test]
    fn part1_example() {
        assert_eq!(part1(&parse(SAMPLE)), 18);
    }

    #[test]
    fn part2_example() {
        assert_eq!(part2(&parse(SAMPLE)), 9);
    }
}
