use crate::{Instruction, Position};

pub enum Direction {
    North,
    West,
    South,
    East,
}

pub fn solve_part(input: &str) -> Result<i32, Box<dyn std::error::Error>> {
    let commands: Vec<Instruction> = input
        .trim()
        .split(", ")
        .map(|l| l.parse().unwrap())
        .collect();
    let mut direction = Direction::North;
    let mut position: Position = Position::default();
    let mut visited = std::collections::HashSet::new();
    visited.insert(position.clone());
    for command in commands {
        match (command, direction) {
            (Instruction::Right(v), Direction::North)
            | (Instruction::Left(v), Direction::South) => {
                direction = Direction::East;
                for _ in 1..=v {
                    position.x += 1;
                    if !visited.insert(position.clone()) {
                        return Ok(position.manhattan_distance());
                    }
                }
            }
            (Instruction::Right(v), Direction::South)
            | (Instruction::Left(v), Direction::North) => {
                direction = Direction::West;
                for _ in 1..=v {
                    position.x -= 1;
                    if !visited.insert(position.clone()) {
                        return Ok(position.manhattan_distance());
                    }
                }
            }
            (Instruction::Right(v), Direction::West) | (Instruction::Left(v), Direction::East) => {
                direction = Direction::North;
                for _ in 1..=v {
                    position.y += 1;
                    if !visited.insert(position.clone()) {
                        return Ok(position.manhattan_distance());
                    }
                }
            }
            (Instruction::Right(v), Direction::East) | (Instruction::Left(v), Direction::West) => {
                direction = Direction::South;
                for _ in 1..=v {
                    position.y -= 1;
                    if !visited.insert(position.clone()) {
                        return Ok(position.manhattan_distance());
                    }
                }
            }
        }
    }
    Ok(position.manhattan_distance())
}

#[cfg(test)]
mod tests {
    use super::solve_part;

    #[test]
    fn test_solve_part2() {
        let input = "R8, R4, R4, R8";
        assert_eq!(solve_part(&input).unwrap(), 4);
    }
}
