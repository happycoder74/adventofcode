use crate::get_md5;

pub fn solve_part(door_id: &str) -> Result<String, ()> {
    let mut password = String::new();
    let mut index = 0;
    loop {
        let code = format!("{}{}", door_id, index);
        let hash = get_md5(&code);
        if hash.starts_with("00000") {
            password.push(hash.chars().nth(5).unwrap());
            println!("{password}");
            if password.len() == 8 {
                break;
            }
        }
        index += 1;
    }
    Ok(password)
}
