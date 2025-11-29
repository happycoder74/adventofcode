use crate::get_room_name;
use crate::sector_id;
use crate::validate_room;

fn rotate_string(input: &str, rotation: usize) -> String {
    let mut new_string = String::new();
    for c in input.chars() {
        if c.is_alphabetic() {
            let code = c.to_ascii_lowercase() as u8 - 'a'.to_ascii_lowercase() as u8;
            let rotated_code = (code as usize + rotation) % 26;
            let new_code = rotated_code as u8 + 'a'.to_ascii_lowercase() as u8;
            new_string.push(new_code as char);
        } else {
            new_string.push(c);
        }
    }
    new_string
}

pub fn solve_part(input: &Vec<&str>) -> Result<usize, Box<dyn std::error::Error>> {
    let valid_rooms = input
        .iter()
        .filter(|room| validate_room(room))
        .collect::<Vec<&&str>>();

    for room in valid_rooms {
        let room_id = sector_id(room);
        let name = get_room_name(room);
        println!("{} - {}", room_id, rotate_string(&name, room_id));
    }
    Ok(0)
}

#[cfg(test)]
mod tests {
    use super::rotate_string;

    #[test]
    fn test_rotate_string_0() {
        let s = "abcdef";
        assert_eq!(rotate_string(s, 0), "abcdef");
    }

    #[test]
    fn test_rotate_string_with_non_alphabetical_5() {
        let s = "abc-def";
        assert_eq!(rotate_string(s, 5), "fgh-ijk");
    }

    #[test]
    fn test_rotate_string_5() {
        let s = "abcdef";
        assert_eq!(rotate_string(s, 5), "fghijk");
    }

    #[test]
    fn test_rotate_string_26() {
        let s = "abcdef";
        assert_eq!(rotate_string(s, 26), "abcdef");
    }

    #[test]
    fn test_rotate_string_28() {
        let s = "abcdef";
        assert_eq!(rotate_string(s, 28), "cdefgh");
    }
}
