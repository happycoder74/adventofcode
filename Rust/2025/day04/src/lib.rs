use std::collections::HashSet;
pub mod part1;
pub mod part2;

struct Grid {
    grid: HashSet<(i32, i32)>,
}

impl Grid {
    fn new() -> Self {
        Self {
            grid: HashSet::new(),
        }
    }
    fn neighbours(&self, location: &(i32, i32)) -> usize {
        let (r, c) = location;
        let mut count: usize = 0;
        for dr in -1..=1 {
            for dc in -1..=1 {
                if !(dc == 0 && dr == 0) && self.grid.contains(&(r + dr, c + dc)) {
                    count += 1;
                }
            }
        }
        count
    }

    fn accessible(&self) -> usize {
        self.grid
            .iter()
            .filter(|location| self.neighbours(location) < 4)
            .count()
    }

    fn remove_accessible(&mut self) -> usize {
        let old_size = self.grid.len();
        let mut removable = self
            .grid
            .iter()
            .filter(|location| self.neighbours(location) < 4)
            .map(|(r, c)| (*r, *c))
            .collect::<Vec<_>>();

        for item in removable.drain(0..) {
            self.grid.remove(&item);
        }

        old_size - self.grid.len()
    }
}
