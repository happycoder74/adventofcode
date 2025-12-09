use std::collections::HashSet;

pub mod connection;
pub mod junctionbox;
pub mod part1;
pub mod part2;

use connection::Connection;
use junctionbox::JunctionBox;

#[derive(Eq, Default, Debug, Clone)]
struct Circuit {
    c: HashSet<JunctionBox>,
}

impl Circuit {
    fn contains(&self, junctionbox: &JunctionBox) -> bool {
        self.c.contains(junctionbox)
    }

    fn insert(&mut self, junctionbox: &JunctionBox) {
        self.c.insert(*junctionbox);
    }

    fn new() -> Self {
        Self { c: HashSet::new() }
    }

    fn from(box1: &JunctionBox, box2: &JunctionBox) -> Self {
        let mut circuit = Circuit::new();
        circuit.insert(box1);
        circuit.insert(box2);
        circuit
    }
}

impl Ord for Circuit {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        let length = self.c.len();
        length.cmp(&other.c.len())
    }
}

impl PartialOrd for Circuit {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        let length = self.c.len();
        length.partial_cmp(&other.c.len())
    }
}

impl PartialEq for Circuit {
    fn eq(&self, other: &Self) -> bool {
        self.c.len() == other.c.len()
    }
}
