fn reductions(s: &str) -> usize {
    let mut stack = Vec::new();
    for c in s.chars() {
        let ch = c as u8;
        if let Some(&top) = stack.last()
            && ch ^ top == 0x20
        {
            stack.pop();
        } else {
            stack.push(ch);
        }
    }

    stack.len()
}

#[must_use]
pub fn part1(input: &str) -> usize {
    reductions(input)
}

#[must_use]
pub fn part2(input: &str) -> usize {
    let mut lengths = Vec::new();
    for c in "abcdefghijklmnopqrstuvwxyz".chars() {
        let reduced_length = reductions(&input.replace([c, c.to_ascii_uppercase()], ""));
        lengths.push(reduced_length);
    }

    *lengths.iter().min().unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    const DATA: [(&str, usize); 6] = [
        ("Aa", 0),
        ("aA", 0),
        ("abBA", 0),
        ("abAB", 4),
        ("aabAAB", 6),
        ("dabAcCaCBAcCcaDA", 10),
    ];

    #[test]
    #[allow(non_snake_case)]
    fn test_Aa() {
        let result = part1(DATA[0].0);
        assert_eq!(DATA[0].1, result);
    }

    #[test]
    #[allow(non_snake_case)]
    fn test_aA() {
        let result = part1(DATA[1].0);
        assert_eq!(DATA[1].1, result);
    }

    #[test]
    #[allow(non_snake_case)]
    fn test_abBa() {
        let result = part1(DATA[2].0);
        assert_eq!(DATA[2].1, result);
    }

    #[test]
    #[allow(non_snake_case)]
    fn test_abAB() {
        let result = part1(DATA[3].0);
        assert_eq!(DATA[3].1, result);
    }

    #[test]
    #[allow(non_snake_case)]
    fn test_aabAAB() {
        let result = reductions(DATA[4].0);
        assert_eq!(DATA[4].1, result);
    }
    #[test]
    fn test_part_1() {
        let result = part1(DATA[5].0);
        assert_eq!(DATA[5].1, result);
    }
    #[test]
    fn test_part_2() {
        let result = part2(DATA[5].0);
        assert_eq!(4, result);
    }
}
