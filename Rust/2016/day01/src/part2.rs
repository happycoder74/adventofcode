pub enum Direction {
    North,
    West,
    South,
    East,
}

pub fn solve_part(input: &str) -> Result<i32, Box<dyn std::error::Error>> {
    let commands: Vec<_> = input.trim().split(", ").collect();
    let mut direction = Direction::North;
    let mut position: (i32, i32) = (0, 0);
    let mut visited = std::collections::HashSet::new();
    visited.insert(position);
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
            for _ in 1..=steps {
                match direction {
                    Direction::North => position = (position.0, position.1 + 1),
                    Direction::South => position = (position.0, position.1 - 1),
                    Direction::East => position = (position.0 + 1, position.1),
                    Direction::West => position = (position.0 - 1, position.1),
                }
                let result = visited.insert(position);
                if !result {
                    return Ok(position.0.abs() + position.1.abs());
                }
            }
        }
    }
    println!("Ends up here");
    Ok(position.0.abs() + position.1.abs())
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
