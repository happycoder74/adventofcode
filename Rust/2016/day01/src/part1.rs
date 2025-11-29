use crate::Direction;
use crate::Instruction;
use crate::Position;

pub fn solve_part(input: &str) -> Result<i32, Box<dyn std::error::Error>> {
    let commands: Vec<Instruction> = input
        .trim()
        .split(", ")
        .map(|l| l.parse().unwrap())
        .collect();
    let mut direction = Direction::North;
    let mut position = Position::default();

    for command in commands {
        match (command, direction) {
            (Instruction::Right(v), Direction::North)
            | (Instruction::Left(v), Direction::South) => {
                position.x = position.x + v;
                direction = Direction::East;
            }
            (Instruction::Right(v), Direction::South)
            | (Instruction::Left(v), Direction::North) => {
                position.x = position.x - v;
                direction = Direction::West;
            }
            (Instruction::Right(v), Direction::West) | (Instruction::Left(v), Direction::East) => {
                position.y = position.y + v;
                direction = Direction::North;
            }
            (Instruction::Right(v), Direction::East) | (Instruction::Left(v), Direction::West) => {
                position.y = position.y - v;
                direction = Direction::South;
            }
        };
    }
    Ok(position.x.abs() + position.y.abs())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        let input = "R5, L5, R5, R3";
        match solve_part(&input) {
            Ok(x) => assert_eq!(x, 12),
            Err(_) => assert!(false),
        }
    }
}
