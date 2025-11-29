use crate::is_triangle;

pub fn parse_input(input: &str) -> Vec<Vec<u32>> {
    let mut lines = input.lines();
    let mut result: Vec<Vec<u32>> = vec![];

    loop {
        let l1: Vec<&str> = match lines.next() {
            Some(x) => x.split_whitespace().collect(),
            None => break,
        };
        let l2: Vec<&str> = match lines.next() {
            Some(x) => x.split_whitespace().collect(),
            None => break,
        };
        let l3: Vec<&str> = match lines.next() {
            Some(x) => x.split_whitespace().collect(),
            None => break,
        };

        let c1: Vec<u32> = vec![
            l1[0].parse().unwrap(),
            l2[0].parse().unwrap(),
            l3[0].parse().unwrap(),
        ];
        let c2: Vec<u32> = vec![
            l1[1].parse().unwrap(),
            l2[1].parse().unwrap(),
            l3[1].parse().unwrap(),
        ];
        let c3: Vec<u32> = vec![
            l1[2].parse().unwrap(),
            l2[2].parse().unwrap(),
            l3[2].parse().unwrap(),
        ];
        result.push(c1);
        result.push(c2);
        result.push(c3);
    }

    result
}

pub fn solve_part(input: &Vec<Vec<u32>>) -> Result<usize, ()> {
    Ok(input.iter().filter(|s| is_triangle(s)).count())
}

// #[cfg(test)]
// mod tests {
//     use super::solve_part;
//
//     #[test]
//     fn test_solve_part() {
//         let input = vec![vec![5, 10, 25]];
//         assert_eq!(solve_part(&input).unwrap(), 0);
//     }
// }
