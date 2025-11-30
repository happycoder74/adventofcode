use std::collections::HashMap;

pub fn solve_part(input: &Vec<&str>) -> Result<String, ()> {
    let mut decoded = String::new();
    for column in 0..input[0].len() {
        let mut letter_map = HashMap::new();
        for row in input {
            let c = row.chars().nth(column).unwrap();
            *letter_map.entry(c).or_insert(0) += 1;
        }

        let most_common = letter_map.iter().max_by_key(|(_, v)| *v).unwrap();
        decoded.push(*most_common.0);
    }

    Ok(decoded)
}

#[cfg(test)]
mod tests {
    use super::solve_part;

    #[test]
    fn test_solve_part() {
        let test_data = "eedadn
drvtee
eandsr
raavrd
atevrs
tsrnev
sdttsa
rasrtv
nssdts
ntnada
svetve
tesnvt
vntsnd
vrdear
dvrsen
enarar";
        let input: Vec<&str> = test_data.lines().collect();
        assert_eq!(solve_part(&input).unwrap(), "easter");
    }
}
