use crate::is_triangle;

pub fn parse_input(input: &str) -> Vec<Vec<u32>> {
    let lines: Vec<Vec<&str>> = input
        .lines()
        .map(|line| line.split_whitespace().collect())
        .collect();

    let mut result: Vec<Vec<u32>> = vec![];

    for line in lines {
        let num_vec: Vec<u32> = line.iter().map(|num| num.parse().unwrap()).collect();
        result.push(num_vec);
    }

    result
}

pub fn solve_part(input: &Vec<Vec<u32>>) -> Result<usize, ()> {
    Ok(input.iter().filter(|s| is_triangle(s)).count())
}

#[cfg(test)]
mod tests {
    use super::solve_part;

    #[test]
    fn test_solve_part() {
        let input = vec![vec![5, 10, 25]];
        assert_eq!(solve_part(&input).unwrap(), 0);
    }
}
