use crate::Instruction;
use crate::Position;

pub fn solve_part(instructions: &Vec<Vec<Instruction>>) -> Result<String, ()> {
    let grid = vec![
        vec!['1', '2', '3'],
        vec!['4', '5', '6'],
        vec!['7', '8', '9'],
    ];
    let mut result = String::new();

    let mut start_position = Position::new(1, 1);
    for row in instructions {
        for instruction in row {
            match instruction {
                Instruction::Up => {
                    if start_position.y > 0 {
                        start_position.y -= 1;
                    }
                }
                Instruction::Down => {
                    if start_position.y < 2 {
                        start_position.y += 1;
                    }
                }
                Instruction::Left => {
                    if start_position.x > 0 {
                        start_position.x -= 1;
                    }
                }
                Instruction::Right => {
                    if start_position.x < 2 {
                        start_position.x += 1;
                    }
                }
            }
        }
        result.push(grid[start_position.y][start_position.x]);
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
        assert_eq!(solve_part(&instructions).unwrap(), "1985");
    }
}
