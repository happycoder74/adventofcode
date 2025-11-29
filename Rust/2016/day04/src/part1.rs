use crate::sector_id;
use crate::validate_room;

pub fn solve_part(input: &Vec<&str>) -> Result<usize, Box<dyn std::error::Error>> {
    let res = input
        .iter()
        .filter(|room| validate_room(room))
        .map(|room| sector_id(room))
        .sum();

    Ok(res)
}

#[cfg(test)]
mod tests {
    use super::solve_part;

    #[test]
    fn test_solve_part() {
        let rooms = vec![
            "aaaaa-bbb-z-y-x-123[abxyz]",
            "a-b-c-d-e-f-g-h-987[abcde]",
            "not-a-real-room-404[oarel]",
            "totally-real-room-200[decoy]",
        ];
        assert_eq!(solve_part(&rooms).unwrap(), 1514);
    }
}
