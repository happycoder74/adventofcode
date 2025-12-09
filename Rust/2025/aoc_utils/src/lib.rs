use std::error::Error;
use std::fmt::Display;
use std::path::PathBuf;

#[derive(Debug)]
pub struct NotImplementedError {
    text: String,
}

impl NotImplementedError {
    #[allow(clippy::must_use_candidate)]
    pub fn new(value: &str) -> Self {
        Self {
            text: value.to_string(),
        }
    }
}

impl Default for NotImplementedError {
    fn default() -> Self {
        Self {
            text: String::from("Not implemented"),
        }
    }
}

impl Error for NotImplementedError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        None
    }
}

impl Display for NotImplementedError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.text)
    }
}

#[allow(clippy::missing_errors_doc)]
pub fn read_input(day: u32) -> Result<String, Box<dyn std::error::Error>> {
    let aoc_path = std::env::var("AOC_DATA_LOCATION")?;
    let mut path = PathBuf::new();
    path.push(aoc_path);
    path.push("2025");
    path.push(format!("{day:02}"));
    path.push("input.txt");

    // println!("Read from '{}'", path.display());
    let content = std::fs::read_to_string(path)?;
    Ok(content)
}

#[derive(Debug, Eq, Hash, PartialEq)]
pub struct Location<T> {
    pub x: T,
    pub y: T,
}

impl<T: std::str::FromStr> std::str::FromStr for Location<T> {
    type Err = T::Err;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut loc = s.split(',');
        let x: T = loc.next().unwrap().parse::<T>()?;
        let y: T = loc.next().unwrap().parse()?;

        Ok(Self { x, y })
    }
}
