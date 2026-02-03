use std::collections::HashMap;

use aoc_utils::{AocError, aoc_get_data};

fn parse_input(input: &str) -> Result<Vec<&str>, AocError> {
    Ok(input.lines().collect::<Vec<&str>>())
}

const LIMIT: usize = 100_000;

struct FileSystem<'a> {
    sizes: HashMap<Vec<&'a str>, usize>,
}

impl<'a> FileSystem<'a> {
    fn new(input: &[&'a str]) -> FileSystem<'a> {
        let mut sizes = HashMap::new();
        let mut curdir = vec![];
        for line in input {
            if line.starts_with("$ cd ") {
                if let Some((_, dest)) = line.rsplit_once(" ") {
                    match dest {
                        ".." => {
                            curdir.pop();
                        }
                        "/" => {}
                        subdir => {
                            curdir.push(subdir);
                        }
                    }
                }
            } else if let Some(s) = line.chars().next()
                && s.is_digit(10)
            {
                if let Some((size, _)) = line.split_once(" ") {
                    for sub in 0..=curdir.len() {
                        *sizes.entry(curdir[..sub].to_vec()).or_default() +=
                            size.parse::<usize>().unwrap();
                    }
                }
            }
        }
        Self { sizes }
    }
}

fn solve_part_1(fs: &FileSystem) -> Result<usize, String> {
    let result = fs.sizes.values().filter(|&&v| v <= LIMIT).sum();

    Ok(result)
}

const TOTAL_SIZE: usize = 70_000_000;
const NEEDED_SIZE: usize = 30_000_000;

fn solve_part_2(fs: &FileSystem) -> Result<usize, String> {
    let used_size = fs.sizes.get(&Vec::new()).ok_or("Error in sizes")?;
    let target_size = NEEDED_SIZE - (TOTAL_SIZE - used_size);
    let result = fs
        .sizes
        .values()
        .filter(|&&v| v >= target_size)
        .min()
        .ok_or("Empty iterator")?;
    Ok(*result)
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "07");
    let start = std::time::Instant::now();
    let input = parse_input(input).unwrap();
    let fs = FileSystem::new(&input);
    println!("Prep time: {:?}", start.elapsed());

    let start = std::time::Instant::now();
    match solve_part_1(&fs) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&fs) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 2: {result} - {duration:?}");
        }
        Err(e) => println!("Part2: Error '{e}'"),
    }
    println!("\nTotal time elapsed: {:?}", main_start.elapsed());
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: &str = "$ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k";

    #[test]
    fn test_part_1() {
        let input = parse_input(DATA).unwrap();
        let fs = FileSystem::new(&input);
        let result = solve_part_1(&fs).unwrap();
        assert_eq!(95437, result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA).unwrap();
        let fs = FileSystem::new(&input);
        let result = solve_part_2(&fs).unwrap();
        assert_eq!(24933642, result);
    }

    #[test]
    fn test_total_size() {
        let input = parse_input(DATA).unwrap();
        let fs = FileSystem::new(&input);
        assert_eq!(48381165, *fs.sizes.get(&Vec::new()).unwrap())
    }
}
