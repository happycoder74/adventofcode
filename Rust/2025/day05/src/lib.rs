pub mod part1;
pub mod part2;

#[derive(Copy, Clone, Debug)]
pub struct Entry {
    start: usize,
    end: usize,
}

impl Entry {
    fn len(&self) -> usize {
        if self.start > self.end {
            println!("{} - {}", self.start, self.end);
            panic!();
        }
        self.end - self.start + 1
    }
}
