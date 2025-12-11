#![allow(unused_variables)]
use crate::Entry;
use aoc_utils::NotImplementedError;
use std::collections::VecDeque;

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str) -> Result<usize, NotImplementedError> {
    let ingredients = input.split("\n\n").next().unwrap();
    let mut parsed = ingredients
        .lines()
        .map(|s| {
            let mut iterator = s.trim().split('-').map(|n| n.parse::<usize>().unwrap());
            Entry {
                start: iterator.next().unwrap(),
                end: iterator.next().unwrap(),
            }
        })
        .collect::<VecDeque<_>>();
    let mut result: Vec<Entry> = vec![];

    while !parsed.is_empty() {
        let mut entry_changed: bool = false;
        let mut entry = parsed.pop_front().unwrap();
        for item in &result {
            if item.start <= entry.start && entry.start <= item.end {
                entry.start = item.end + 1;
                entry_changed = true;
                if entry.start <= entry.end {
                    parsed.push_back(entry);
                }
                break;
            }
            if item.start <= entry.end && entry.end <= item.end {
                entry.end = item.start - 1;
                entry_changed = true;
                if entry.start <= entry.end {
                    parsed.push_back(entry);
                }
                break;
            }
            if entry.start <= item.start && item.end <= entry.end {
                let new_entry = Entry {
                    start: item.end + 1,
                    end: entry.end,
                };
                entry.end = item.start - 1;
                entry_changed = true;
                if entry.start <= entry.end {
                    parsed.push_back(entry);
                }
                parsed.push_back(new_entry);
            }
        }
        if !entry_changed {
            result.push(entry);
        }
    }

    Ok(result.iter().map(crate::Entry::len).sum::<usize>())
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "3-5
10-14
16-20
12-18

1
5
8
11
17
32
";

        assert_eq!(super::solve_part(input).unwrap(), 14);
    }
}
