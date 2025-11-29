use std::path::PathBuf;

pub fn read_input() -> Result<String, Box<dyn std::error::Error>> {
    let aoc_path = std::env::var("AOC_DATA_LOCATION")?;
    let mut path = PathBuf::new();
    path.push(aoc_path);
    path.push("2016");
    path.push("01");
    path.push("input.txt");

    println!("Read from '{}'", path.display());
    let content = std::fs::read_to_string(path)?;
    Ok(content)
}
