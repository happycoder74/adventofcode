use aoc_utils::{AocError, AocPartResult, AocResult, AocReturn};
use std::{io::Write, time::Instant};

struct AutoFlush<W: Write>(W);

impl<W: Write> Write for AutoFlush<W> {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let n = self.0.write(buf)?;
        self.0.flush()?;
        Ok(n)
    }

    fn flush(&mut self) -> std::io::Result<()> {
        self.0.flush()
    }
}

pub struct Day2015_04<'a>(&'a [u8]);

impl<'a> Day2015_04<'_> {
    fn solve_part_1(&self) -> Result<AocPartResult<u32>, AocError> {
        let start_time = Instant::now();
        let mut root = md5::Context::new();
        root.consume(self.0.trim_ascii());

        for val in 0.. {
            let mut context = root.clone();
            context.consume(format!("{val}"));
            let hash = context.finalize().0;
            if matches!(hash, [0, 0, b, ..] if b >> 4 == 0) {
                println!();
                return Ok(AocPartResult {
                    result: AocResult::new(val),
                    duration: start_time.elapsed(),
                });
            }
        }
        Err(AocError::new("Solution not found"))
    }

    fn solve_part_2(&self) -> Result<AocPartResult<u32>, AocError> {
        let start_time = Instant::now();
        let mut root = md5::Context::new();
        root.consume(self.0.trim_ascii());

        let stdout = std::io::stdout();
        let mut out = AutoFlush(stdout.lock());

        for val in 0.. {
            let mut context = root.clone();
            context.consume(format!("{val}"));
            let hash = context.finalize().0;
            if matches!(hash, [0, 0, b, ..] if b >> 4 == 0) {
                println!();
                return Ok(AocPartResult {
                    result: AocResult::new(val),
                    duration: start_time.elapsed(),
                });
            }
            if val % 100000 == 0 {
                write!(out, ".").unwrap();
            }
        }
        unreachable!();
    }

    fn solve_all(self) -> AocReturn<u32, u32> {
        let return1 = self.solve_part_1();
        let return2 = self.solve_part_2();
        AocReturn::from_parts(return1, return2)
    }
}

fn main() {
    let input =
        include_bytes!(concat!(env!("AOC_DATA_LOCATION"), "/2015/04/input.txt")).trim_ascii();

    let day = Day2015_04(input);

    let results = day.solve_all();

    match results.part1 {
        Ok(x) => println!("Part 1: {}", x.result),
        Err(e) => eprintln!("{e}"),
    }
    // aoc_utils::report(results);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_solve_part_1() {
        let data = b"abcdef";
        let day = Day2015_04(data);
        let result = day.solve_part_1();
        assert_eq!(609043u32, u32::from(result.unwrap().result))
    }
}
