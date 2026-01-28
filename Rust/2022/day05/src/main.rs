use aoc_utils::aoc_get_data;
use std::{collections::VecDeque, error::Error, fmt::Display};

#[derive(Debug)]
enum AocError {
    NotImplementedError,
    InputError,
    StackIndexError,
    EmptyStack,
}

impl Error for AocError {}

impl Display for AocError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::NotImplementedError => write!(f, "NotImplementedError"),
            Self::InputError => write!(f, "Input error"),
            Self::EmptyStack => write!(f, "Empty stack"),
            Self::StackIndexError => write!(f, "Stack Index Error"),
        }
    }
}

#[derive(Debug, Eq, PartialEq, Clone, Copy)]
struct BoxDef {
    id: u8,
}

#[derive(Debug, Eq, PartialEq, Clone, Copy)]
struct Instruction {
    number: u32,
    source: u32,
    destination: u32,
}

#[cfg(test)]
impl Instruction {
    fn new(number: u32, source: u32, destination: u32) -> Self {
        Self {
            number,
            source,
            destination,
        }
    }
}
impl Display for Instruction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Move {} boxes from bin {} to bin {}",
            self.number, self.source, self.destination
        )
    }
}

fn parse_input(input: &str) -> Result<(Vec<Vec<BoxDef>>, Vec<Instruction>), Box<dyn Error>> {
    let (boxes, instructions) = input.split_once("\n\n").ok_or(AocError::InputError)?;
    let instruction_list = instructions
        .lines()
        .map(|line| {
            let content = line.split_ascii_whitespace().collect::<Vec<_>>();
            Instruction {
                number: content[1].parse().unwrap(),
                source: content[3].parse().unwrap(),
                destination: content[5].parse().unwrap(),
            }
        })
        .collect::<Vec<_>>();

    let mut box_lines = boxes.split("\n").map(str::to_owned).collect::<Vec<_>>();

    let n_bins = box_lines
        .pop()
        .unwrap()
        .split_ascii_whitespace()
        .last()
        .unwrap()
        .parse::<usize>()
        .unwrap();
    let mut bins = vec![vec![]; n_bins];

    let reversed_box_lines = box_lines.iter().rev();

    for line in reversed_box_lines {
        let bytes_line = line.as_bytes();
        match bytes_line[1] {
            b'1'..=b'9' => break,
            _ => (),
        }
        for (i, box_item) in line.as_bytes().chunks(4).enumerate() {
            if box_item[0] == b'[' {
                bins[i].push(BoxDef { id: box_item[1] })
            }
        }
    }

    Ok((bins, instruction_list))
}

fn solve_part_1(input: &(Vec<Vec<BoxDef>>, Vec<Instruction>)) -> Result<String, Box<dyn Error>> {
    let mut stacks = input.0.clone();
    for instruction in input.1.clone() {
        for _ in 0..instruction.number {
            let source_stack = stacks
                .get_mut((instruction.source - 1) as usize)
                .ok_or(AocError::StackIndexError)?;
            let b = source_stack.pop().ok_or(AocError::EmptyStack)?;
            let dest_stack = stacks
                .get_mut((instruction.destination - 1) as usize)
                .ok_or(AocError::StackIndexError)?;
            dest_stack.push(b);
        }
    }

    let result = stacks
        .iter_mut()
        .map(|stack| stack.pop().unwrap().id as char)
        .collect::<String>();
    Ok(result)
}

fn solve_part_2(input: &(Vec<Vec<BoxDef>>, Vec<Instruction>)) -> Result<String, Box<dyn Error>> {
    let mut stacks = input.0.clone();
    let mut offload = VecDeque::new();
    for instruction in input.1.clone() {
        for _ in 0..instruction.number {
            let source_stack = stacks
                .get_mut((instruction.source - 1) as usize)
                .ok_or(AocError::StackIndexError)?;
            let b = source_stack.pop().ok_or(AocError::EmptyStack)?;
            offload.push_front(b);
        }
        while let Some(bb) = offload.pop_front() {
            let dest_stack = stacks
                .get_mut((instruction.destination - 1) as usize)
                .ok_or(AocError::StackIndexError)?;
            dest_stack.push(bb);
        }
    }
    let result = stacks
        .iter_mut()
        .map(|stack| stack.pop().unwrap().id as char)
        .collect::<String>();
    Ok(result)
}

fn main() {
    let main_start = std::time::Instant::now();
    let input = aoc_get_data!("2022", "05");
    let commands = parse_input(&input).unwrap();

    let start = std::time::Instant::now();
    match solve_part_1(&commands) {
        Ok(result) => {
            let duration = start.elapsed();
            println!("Part 1: {result} - {duration:?}");
        }
        Err(e) => println!("Part1: Error '{e}'"),
    }
    let start = std::time::Instant::now();
    match solve_part_2(&commands) {
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

    const DATA: &str = "    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2";

    #[test]
    fn test_parser() {
        let (boxes, instructions) = parse_input(DATA).unwrap();
        assert_eq!(3, boxes.len());
        assert_eq!(
            vec![
                Instruction::new(1, 2, 1),
                Instruction::new(3, 1, 3),
                Instruction::new(2, 2, 1),
                Instruction::new(1, 1, 2),
            ],
            instructions
        );
        let first_box = boxes[0][0];
        assert_eq!(BoxDef { id: b'Z' }, first_box);
        assert_eq!(2, boxes[0].len());
        assert_eq!(vec![BoxDef { id: b'Z' }, BoxDef { id: b'N' }], boxes[0]);
        assert_eq!(
            vec![
                BoxDef { id: b'M' },
                BoxDef { id: b'C' },
                BoxDef { id: b'D' }
            ],
            boxes[1]
        );
        assert_eq!(vec![BoxDef { id: b'P' }], boxes[2]);
    }
    #[test]
    fn test_part_1() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_1(&input).unwrap();
        assert_eq!("CMZ", result);
    }

    #[test]
    fn test_part_2() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!("MCD", result);
    }
}
