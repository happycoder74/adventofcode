use aoc_utils::AocError;
use std::str::FromStr;

pub enum InstructionId {
    AddX(i32),
    Noop,
}

pub struct Instruction {
    id: InstructionId,
    cycles: u32,
}

impl Instruction {
    fn new(id: InstructionId) -> Self {
        Self {
            cycles: match id {
                InstructionId::Noop => 1,
                InstructionId::AddX(_) => 2,
            },
            id,
        }
    }
}

impl FromStr for Instruction {
    type Err = AocError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        if let Some((_, value)) = s.split_once(" ") {
            let value = value
                .parse::<i32>()
                .map_err(|_| AocError::new("ParseIntError"))?;
            Ok(Instruction::new(InstructionId::AddX(value)))
        } else {
            Ok(Instruction::new(InstructionId::Noop))
        }
    }
}

pub fn parse_input(input: &str) -> Result<Vec<Instruction>, AocError> {
    input.lines().map(|line| line.parse()).collect()
}

pub fn solve_part_1(input: &[Instruction]) -> Result<usize, AocError> {
    let mut cycle = 0i32;
    let mut register: i32 = 1;
    let mut register_vec = Vec::new();

    for instruction in input {
        let wait = instruction.cycles;

        for _ in 0..wait {
            cycle += 1;
            if cycle % 40 == 20 {
                register_vec.push(register * cycle);
            }
        }
        if let InstructionId::AddX(value) = instruction.id {
            register += value;
        }
    }
    Ok(register_vec.iter().sum::<i32>() as usize)
}

pub fn solve_part_2(input: &[Instruction]) -> Result<String, AocError> {
    let mut crt_display = [b' '; 240];
    let mut cycle = 0i32;
    let mut sprite_position: i32 = 1;

    for instruction in input {
        let wait = instruction.cycles;

        for _ in 0..wait {
            if ((sprite_position - 1)..=(sprite_position + 1)).contains(&(cycle % 40)) {
                crt_display[cycle as usize] = b'#';
            }
            cycle += 1;
        }
        if let InstructionId::AddX(value) = instruction.id {
            sprite_position += value;
        }
    }
    let mut result: [&str; 6] = [""; 6];
    for row in 0..6 {
        let start_index = row * 40;
        let end_index = start_index + 40;
        let row_str = str::from_utf8(&crt_display[start_index..end_index]).unwrap();
        result[row] = row_str;
    }

    Ok(String::from("\n") + &result.join("\n"))
}

#[cfg(test)]
mod tests {

    use super::*;

    const DATA: &str = "addx 15
addx -11
addx 6
addx -3
addx 5
addx -1
addx -8
addx 13
addx 4
noop
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx -35
addx 1
addx 24
addx -19
addx 1
addx 16
addx -11
noop
noop
addx 21
addx -15
noop
noop
addx -3
addx 9
addx 1
addx -3
addx 8
addx 1
addx 5
noop
noop
noop
noop
noop
addx -36
noop
addx 1
addx 7
noop
noop
noop
addx 2
addx 6
noop
noop
noop
noop
noop
addx 1
noop
noop
addx 7
addx 1
noop
addx -13
addx 13
addx 7
noop
addx 1
addx -33
noop
noop
noop
addx 2
noop
noop
noop
addx 8
noop
addx -1
addx 2
addx 1
noop
addx 17
addx -9
addx 1
addx 1
addx -3
addx 11
noop
noop
addx 1
noop
addx 1
noop
noop
addx -13
addx -19
addx 1
addx 3
addx 26
addx -30
addx 12
addx -1
addx 3
addx 1
noop
noop
noop
addx -9
addx 18
addx 1
addx 2
noop
noop
addx 9
noop
noop
noop
addx -1
addx 2
addx -37
addx 1
addx 3
noop
addx 15
addx -21
addx 22
addx -6
addx 1
noop
addx 2
addx 1
noop
addx -10
noop
noop
addx 20
addx 1
addx 2
addx 2
addx -6
addx -11
noop
noop
noop";

    #[test]
    fn test_solve_part_1() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_1(&input).unwrap();

        assert_eq!(13140, result)
    }

    const PART2_RESULT: &str = "\n##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....";

    #[test]
    fn test_solve_part_2() {
        let input = parse_input(DATA).unwrap();
        let result = solve_part_2(&input).unwrap();
        assert_eq!(result, PART2_RESULT);
    }
}
