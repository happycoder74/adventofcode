use std::collections::HashMap;
pub mod part1;
pub mod part2;

#[derive(Default, Debug, Hash, Eq, PartialEq, Clone, Copy)]
struct Location {
    x: i32,
    y: i32,
}

impl std::fmt::Display for Location {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl Location {
    fn step(self, x_steps: i32, y_steps: i32) -> Option<Self> {
        if self.x == 0 && x_steps < 0 {
            return None;
        }
        if self.y == 0 && y_steps < 0 {
            return None;
        }
        let x = self.x + x_steps;
        let y = self.y + y_steps;
        Some(Self { x, y })
    }

    fn step_down(self) -> Self {
        self.step(0, 1).unwrap()
    }
}
struct Grid {
    locations: HashMap<Location, char>,
    x_size: i32,
    y_size: i32,
}

impl Grid {
    fn new() -> Self {
        Self {
            locations: HashMap::new(),
            x_size: 0,
            y_size: 0,
        }
    }
    fn insert(&mut self, location: Location, value: char) -> Option<char> {
        let ret = self.locations.insert(location, value);
        if location.x > self.x_size {
            self.x_size = location.x;
        }
        if location.y > self.y_size {
            self.y_size = location.y;
        }
        ret
    }

    fn import(input: &str) -> Self {
        let mut grid = Self::new();
        input.lines().zip(0i32..).for_each(|(line, line_index)| {
            line.trim()
                .chars()
                .zip(0i32..)
                .for_each(|(col, col_index)| {
                    grid.insert(
                        Location {
                            x: col_index,
                            y: line_index,
                        },
                        col,
                    );
                });
        });

        grid
    }
}
