pub mod part1;
pub mod part2;

pub fn validate_room(room: &str) -> bool {
    let mut letters = std::collections::HashMap::new();
    let room_name = get_room_name(room);
    let mut room_name_iter = room_name.chars();

    let validation_key: String = room.split('[').last().unwrap().chars().take(5).collect();
    while let Some(c) = room_name_iter.next() {
        if c.is_ascii_alphabetic() {
            match letters.get(&c) {
                Some(x) => letters.insert(c, x + 1),
                None => letters.insert(c, 1),
            };
        }
    }
    let mut items: Vec<(_, _)> = letters.into_iter().collect();
    items.sort_by_key(|(k, _)| *k);
    items.sort_by_key(|(_, v)| -(*v));
    let top5: String = items.iter().take(5).map(|(k, _)| *k).collect::<String>();

    validation_key == top5
}

pub fn get_room_name(room: &str) -> String {
    let mut return_string = String::new();
    let mut room_iter = room.chars();
    while let Some(c) = room_iter.next() {
        if c.is_numeric() {
            break;
        } else if c.is_ascii_alphabetic() {
            return_string.push(c);
        } else if c == '-' {
            return_string.push(' ');
        }
    }
    return_string.trim().to_string()
}

pub fn sector_id(room: &str) -> usize {
    room.chars()
        .filter(|c| c.is_numeric())
        .collect::<String>()
        .parse::<usize>()
        .unwrap()
}
