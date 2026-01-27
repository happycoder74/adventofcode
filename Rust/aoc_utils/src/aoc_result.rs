use std::convert::From;
use std::fmt::Display;

pub struct AocResult<T> {
    val: T,
}

impl<T> AocResult<T> {
    pub fn new(val: T) -> Self {
        Self { val }
    }
}

impl<T: std::fmt::Display> Display for AocResult<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.val.fmt(f)
    }
}

impl From<AocResult<u32>> for u32 {
    fn from(value: AocResult<u32>) -> Self {
        u32::from(value.val)
    }
}
impl From<AocResult<i32>> for i32 {
    fn from(value: AocResult<i32>) -> Self {
        i32::from(value.val)
    }
}
impl From<AocResult<usize>> for usize {
    fn from(value: AocResult<usize>) -> Self {
        usize::from(value.val)
    }
}
