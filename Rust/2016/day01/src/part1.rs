pub enum Direction {
    North,
    West,
    South,
    East,
}

pub fn solve_part(input: &str) -> Result<i32, Box<dyn std::error::Error>> {
    let commands: Vec<_> = input.trim().split(", ").collect();
    let mut direction = Direction::North;
    let mut position = (0, 0);

    for command in commands {
        let mut comm = command.chars();
        if let Some(dir) = comm.next() {
            let steps_str: String = comm.collect();
            let steps = steps_str.parse::<i32>()?;
            direction = match dir {
                'R' => match direction {
                    Direction::North => Direction::East,
                    Direction::West => Direction::North,
                    Direction::South => Direction::West,
                    Direction::East => Direction::South,
                },
                'L' => match direction {
                    Direction::North => Direction::West,
                    Direction::West => Direction::South,
                    Direction::South => Direction::East,
                    Direction::East => Direction::North,
                },
                _ => panic!("FAIL"),
            };
            match direction {
                Direction::North => position = (position.0, position.1 + steps),
                Direction::South => position = (position.0, position.1 - steps),
                Direction::East => position = (position.0 + steps, position.1),
                Direction::West => position = (position.0 - steps, position.1),
            }
        }
    }
    Ok(position.0.abs() + position.1.abs())
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
