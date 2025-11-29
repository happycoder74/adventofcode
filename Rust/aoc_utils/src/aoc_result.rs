use std::convert::From;
use std::fmt::Display;

pub enum AocResult {
    Usize(usize),
    U32(u32),
    U64(u64),
    I32(i32),
    Str(String),
}

impl Display for AocResult {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            AocResult::Usize(x) => x.fmt(f),
            AocResult::U64(x) => x.fmt(f),
            AocResult::U32(x) => x.fmt(f),
            AocResult::I32(x) => x.fmt(f),
            AocResult::Str(x) => x.fmt(f),
        }
    }
}

impl From<AocResult> for u32 {
    fn from(value: AocResult) -> Self {
        match value {
            AocResult::Usize(x) => x as u32,
            AocResult::U64(x) => x as u32,
            AocResult::U32(x) => x,
            AocResult::I32(x) => x as u32,
            AocResult::Str(x) => x.parse::<u32>().unwrap(),
        }
    }
}

impl From<AocResult> for i32 {
    fn from(value: AocResult) -> Self {
        match value {
            AocResult::Usize(x) => x as i32,
            AocResult::U64(x) => x as i32,
            AocResult::U32(x) => x as i32,
            AocResult::I32(x) => x,
            AocResult::Str(x) => x.parse::<i32>().unwrap(),
        }
    }
}

impl From<usize> for AocResult {
    fn from(value: usize) -> Self {
        AocResult::Usize(value)
    }
}

impl From<u64> for AocResult {
    fn from(value: u64) -> Self {
        AocResult::U64(value)
    }
}

impl From<u32> for AocResult {
    fn from(value: u32) -> Self {
        AocResult::U32(value)
    }
}

impl From<String> for AocResult {
    fn from(value: String) -> Self {
        AocResult::Str(value)
    }
}
