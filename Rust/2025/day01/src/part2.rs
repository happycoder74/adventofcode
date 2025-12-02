use crate::Instruction;

pub fn solve_part(input: &Vec<&str>) -> Result<i32, ()> {
    let mut current_value = 50;
    let mut num_zeros = 0;

    for code in input {
        let instruction = code.parse::<Instruction>().unwrap();
        let old_value = current_value;
        match instruction {
            Instruction::Left(amount) => {
                // Turn dial left
                current_value -= amount;
                num_zeros += (amount / 100).abs();
                current_value = current_value.rem_euclid(100);
                if current_value >= old_value && old_value != 0 {
                    num_zeros += 1;
                }
            }
            Instruction::Right(amount) => {
                // Turn dial right
                current_value += amount;
                num_zeros += (amount / 100).abs();
                current_value = current_value.rem_euclid(100);
                if current_value <= old_value && current_value != 0 {
                    num_zeros += 1;
                }
            }
        }
        if current_value % 100 == 0 {
            num_zeros += 1;
        }
    }
    Ok(num_zeros)
}

#[cfg(test)]
mod tests {
    #[test]
    fn test_solve_part() {
        let input = vec![
            "L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82",
        ];

        assert_eq!(super::solve_part(&input).unwrap(), 6);
    }
}
