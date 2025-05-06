pub mod aoc_macro;
pub mod aoc_result;
pub mod input;
pub mod output;
pub mod types;

pub use aoc_result::AocResult;
pub use input::read_input;
pub use output::report;
pub use types::{AocError, AocPartReturn, AocReturn, Puzzle};
