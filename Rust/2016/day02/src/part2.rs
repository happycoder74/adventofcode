use crate::Instruction;
use crate::Position;

pub fn solve_part(instructions: &Vec<Vec<Instruction>>) -> Result<String, ()> {
    let grid = vec![
        vec!['X', 'X', '1', 'X', 'X'],
        vec!['X', '2', '3', '4', 'X'],
        vec!['5', '6', '7', '8', '9'],
        vec!['X', 'A', 'B', 'C', 'X'],
        vec!['X', 'X', 'D', 'X', 'X'],
    ];
    let mut result = String::new();

    let mut position = Position::new(0, 2);
    for row in instructions {
        for instruction in row {
            match instruction {
                Instruction::Up => {
                    if position.y > 0 {
                        if grid[position.y - 1][position.x] != 'X' {
                            position.y -= 1;
                        }
                    }
                }
                Instruction::Down => {
                    if position.y < 4 {
                        if grid[position.y + 1][position.x] != 'X' {
                            position.y += 1;
                        }
                    }
                }
                Instruction::Left => {
                    if position.x > 0 {
                        if grid[position.y][position.x - 1] != 'X' {
                            position.x -= 1;
                        }
                    }
                }
                Instruction::Right => {
                    if position.x < 4 {
                        if grid[position.y][position.x + 1] != 'X' {
                            position.x += 1;
                        }
                    }
                }
            }
        }
        result.push(grid[position.y][position.x]);
    }
    Ok(result)
}

#[cfg(test)]
mod tests {
    use crate::parse_input;

    use super::solve_part;

    #[test]
    fn test_solve_part() {
        let input = "ULL\nRRDDD\nLURDL\nUUUUD";
        let instructions = parse_input(input);
        assert_eq!(solve_part(&instructions).unwrap(), "5DB3");
        //
    }
}
