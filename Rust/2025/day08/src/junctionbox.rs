use std::{num::ParseIntError, str::FromStr};

#[derive(Default, Hash, Eq, PartialEq, Clone, Copy)]
pub struct JunctionBox {
    x: usize,
    y: usize,
    z: usize,
}

impl std::fmt::Display for JunctionBox {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {}, {})", self.x, self.y, self.z)
    }
}

impl FromStr for JunctionBox {
    type Err = ParseIntError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut items = s.split(',');
        let x = items.next().unwrap().parse::<usize>()?;
        let y = items.next().unwrap().parse::<usize>()?;
        let z = items.next().unwrap().parse::<usize>()?;

        Ok(Self::from(x, y, z))
    }
}

impl std::fmt::Debug for JunctionBox {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {}, {})", self.x, self.y, self.z)
    }
}

impl JunctionBox {
    #[must_use]
    pub fn get_x(&self) -> usize {
        self.x
    }

    fn from(x: usize, y: usize, z: usize) -> Self {
        Self { x, y, z }
    }

    #[must_use]
    pub fn distance(&self, other: &JunctionBox) -> usize {
        self.x.abs_diff(other.x).pow(2)
            + self.y.abs_diff(other.y).pow(2)
            + self.z.abs_diff(other.z).pow(2)
    }
}
