use crate::junctionbox::JunctionBox;
use std::{cmp::Ordering, hash::Hash};

#[derive(Default, Eq)]
pub struct Connection {
    pub j1: JunctionBox,
    pub j2: JunctionBox,
    pub d: usize,
}

impl Hash for Connection {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.j1.hash(state);
        self.j2.hash(state);
        self.d.hash(state);
    }
}

impl Ord for Connection {
    fn cmp(&self, other: &Self) -> Ordering {
        self.partial_cmp(other).unwrap()
    }
}

#[allow(clippy::non_canonical_partial_ord_impl)]
impl PartialOrd for Connection {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        other.d.partial_cmp(&self.d)
    }
}

impl std::fmt::Debug for Connection {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} -> {}: {}", self.j1, self.j2, self.d)
    }
}

impl std::fmt::Display for Connection {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} -> {}: {}", self.j1, self.j2, self.d)
    }
}

impl PartialEq for Connection {
    fn eq(&self, other: &Self) -> bool {
        self.d == other.d
    }
}
