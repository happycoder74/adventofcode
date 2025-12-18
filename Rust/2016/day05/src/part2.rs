use crate::get_md5;

pub fn solve_part(door_id: &str) -> Result<String, ()> {
    let mut password = *b"........";
    let mut index = 0;

    loop {
        let code = format!("{}{}", door_id, index);
        let hash = get_md5(&code);
        if hash.starts_with("00000") {
            if let Some(position) = hash.chars().nth(5).unwrap().to_digit(10) {
                if position < 8 && password[position as usize] == '.' as u8 {
                    let c = hash.chars().nth(6).unwrap();
                    password[position as usize] = c as u8;
                    println!("{:?}", str::from_utf8(&password).unwrap_or(""));
                    if !password.contains(&b'.') {
                        break;
                    }
                }
            }
        }
        index += 1;
    }

    Ok(String::from_utf8_lossy(&password).into_owned())
}
