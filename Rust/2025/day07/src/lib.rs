use std::collections::HashMap;
pub mod part1;
pub mod part2;

#[derive(Default, Debug, Hash, Eq, PartialEq, Clone, Copy)]
struct Location {
    x: u32,
    y: u32,
}

impl std::fmt::Display for Location {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl Location {
    fn step(&self, x_steps: i32, y_steps: i32) -> Self {
        Self {
            x: (self.x as i32 + x_steps) as u32,
            y: (self.y as i32 + y_steps) as u32,
        }
    }

    fn step_down(&self) -> Self {
        self.step(0, 1)
    }
}
struct Grid {
    grid: HashMap<Location, char>,
    x_size: u32,
    y_size: u32,
}

impl Grid {
    fn new() -> Self {
        Self {
            grid: HashMap::new(),
            x_size: 0,
            y_size: 0,
        }
    }
    fn insert(&mut self, location: Location, value: char) -> Option<char> {
        let ret = self.grid.insert(location, value);
        if location.x > self.x_size {
            self.x_size = location.x;
        }
        if location.y > self.y_size {
            self.y_size = location.y;
        }
        ret
    }

    fn print(&self) {
        for y in 0..=self.y_size {
            for x in 0..=self.x_size {
                print!("{}", self.grid.get(&Location { x, y }).unwrap());
            }
            print!("\n");
        }
        print!("\n");
    }

    fn import(input: &str) -> Self {
        let mut grid = Self::new();
        input.lines().enumerate().for_each(|(line_index, line)| {
            line.trim()
                .chars()
                .enumerate()
                .for_each(|(col_index, col)| {
                    grid.insert(
                        Location {
                            x: col_index as u32,
                            y: line_index as u32,
                        },
                        col,
                    );
                });
        });

        grid
    }
}
