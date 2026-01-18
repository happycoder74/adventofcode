use std::{fmt::Display, str::FromStr};

#[derive(Debug, PartialEq, Eq)]
struct ParseDimensionError;

#[derive(Debug, PartialEq, Eq)]
struct ParsePointError;

#[derive(Debug, PartialEq, Eq)]
struct ParseSpecError;

#[derive(Eq, PartialEq, Hash)]
struct Point {
    x: u32,
    y: u32,
}

struct Dimensions {
    width: u32,
    height: u32,
}

impl FromStr for Dimensions {
    type Err = ParseDimensionError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (w, h) = s.split_once('x').ok_or(ParseDimensionError)?;
        Ok(Dimensions {
            width: w.parse::<u32>().map_err(|_| ParseDimensionError)?,
            height: h.parse::<u32>().map_err(|_| ParseDimensionError)?,
        })
    }
}

impl Display for Dimensions {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}x{}", self.width, self.height)
    }
}

struct Spec {
    id: u32,
    location: Point,
    dimensions: Dimensions,
}

impl Spec {
    fn top(&self) -> u32 {
        self.location.y
    }

    fn bottom(&self) -> u32 {
        self.location.y + self.dimensions.height - 1
    }

    fn left(&self) -> u32 {
        self.location.x
    }

    fn right(&self) -> u32 {
        self.location.x + self.dimensions.width - 1
    }
}

impl FromStr for Point {
    type Err = ParsePointError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (x, y) = s.split_once(',').ok_or(ParsePointError)?;
        Ok(Point {
            x: x.parse::<u32>().map_err(|_| ParsePointError)?,
            y: y.parse::<u32>().map_err(|_| ParsePointError)?,
        })
    }
}

impl Display for Point {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl FromStr for Spec {
    type Err = ParseSpecError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let line = s
            .strip_prefix("#")
            .map(|s| s.replace('@', ""))
            .map(|s| s.replace(':', ""))
            .ok_or(ParseSpecError)?;

        let mut line_items = line.split_whitespace();

        Ok(Spec {
            id: line_items
                .next()
                .unwrap()
                .parse()
                .map_err(|_| ParseSpecError)?,
            location: line_items
                .next()
                .unwrap()
                .parse()
                .map_err(|_| ParseSpecError)?,
            dimensions: line_items
                .next()
                .unwrap()
                .parse()
                .map_err(|_| ParseSpecError)?,
        })
    }
}

impl Display for Spec {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "ID: {}, Location: {}, Dimensions: {}",
            self.id, self.location, self.dimensions
        )
    }
}

fn parse_data(input: &str) -> Result<Vec<Spec>, ParseSpecError> {
    input.lines().map(str::parse).collect()
}

fn populate_map(input: &[Spec]) -> Vec<u32> {
    let mut m = vec![0; 1000 * 1000];

    for spec in input {
        for x in spec.left()..=spec.right() {
            for y in spec.top()..=spec.bottom() {
                m[(1000 * y + x) as usize] += 1;
            }
        }
    }

    m
}

fn part1(input: &[Spec]) -> usize {
    let m = populate_map(input);
    m.iter().filter(|v| *v > &1u32).count()
}

fn check_claims(spec: &Spec, m: &[u32]) -> bool {
    for x in spec.left()..=spec.right() {
        for y in spec.top()..=spec.bottom() {
            if m[(1000 * y + x) as usize] != 1 {
                return false;
            }
        }
    }
    true
}

fn part2(input: &[Spec]) -> u32 {
    let m = populate_map(input);
    input.iter().find(|s| check_claims(s, &m)).unwrap().id
}

fn main() {
    let data = include_str!(concat!(
        env!("AOC_DATA_LOCATION"),
        "/2018",
        "/03",
        "/input.txt"
    ));

    if let Ok(input) = parse_data(data) {
        let start = std::time::Instant::now();
        println!("Part 1: {:<20} [{:?}]", part1(&input), start.elapsed());
        let start = std::time::Instant::now();
        println!("Part 2: {:<20} [{:?}]", part2(&input), start.elapsed());
    }
}
