#![allow(unused)]
#![allow(dead_code, unused)]
#![allow(unused_variables)]
use itertools::Itertools;
use std::collections::BinaryHeap;
use std::collections::HashSet;
use std::num::ParseIntError;

use aoc_utils::NotImplementedError;

use crate::{Circuit, Connection, JunctionBox};

#[allow(clippy::missing_errors_doc, clippy::missing_panics_doc)]
pub fn solve_part(input: &str, number_of_pairs: usize) -> Result<usize, NotImplementedError> {
    let mut connections = input
        .lines()
        .map(|line| line.trim().parse::<JunctionBox>().unwrap())
        .combinations(2)
        .map(|c| Connection {
            j1: c[0].clone(),
            j2: c[1].clone(),
            d: c[0].distance(&c[1]),
        })
        .collect::<BinaryHeap<_>>();

    let mut circuits: Vec<HashSet<JunctionBox>> = vec![];
    let mut circuit = std::collections::HashSet::<JunctionBox>::new();
    let mut counter = 0;
    for _ in 0..number_of_pairs {
        let conn = connections.pop().unwrap();
        let box1 = conn.j1;
        let box2 = conn.j2;
        let mut found = false;
        //println!("\nProcessing box1: {} and box2: {}", box1, box2);
        let mut a = circuits
            .iter()
            .enumerate()
            .filter(|(_, c)| c.contains(&box1));
        let mut b = circuits
            .iter()
            .enumerate()
            .filter(|(_, c)| c.contains(&box2));

        match a.next() {
            Some((index_a, c_a)) => match b.next() {
                Some((index_b, c_b)) => {
                    // Do nothing if index_a == index_b (Same circuit)
                    // Merge circuits if index_a != index_b (Both connected, but to different circuits)
                    if index_a != index_b {
                        //println!("Merging circuit {index_b} into {index_a}");
                        let mut circuit: HashSet<JunctionBox> = c_b.union(c_a).copied().collect();
                        circuits[index_a] = circuit;
                        circuits.remove(index_b);
                    } else {
                        //println!("In same circuit. Do nothing!");
                    }
                }
                None => {
                    // Add b to a's circuit.
                    circuits[index_a].insert(box2);
                    //println!("Adding box {box2} to circuit {index_a}");
                    counter += 1;
                }
            },
            None => match b.next() {
                Some((index_b, c_b)) => {
                    // Add a to b's circuit
                    circuits[index_b].insert(box1);
                    //println!("Adding box {box1} to circuit {index_b}");
                    counter += 1;
                }
                None => {
                    // Add a & b to new circuit
                    let mut circuit = HashSet::new();
                    circuit.insert(box1);
                    circuit.insert(box2);
                    circuits.push(circuit);
                    counter += 1;
                    //println!("Adding {box1} and {box2} to new circuit");
                }
            },
        }
        //println!("{} circuits", circuits.len());
        // circuits
        //     .iter()
        //     .enumerate()
        //     .for_each(|(i, c)| println!("{}: {c:?}", i));
    }
    let mut heap: BinaryHeap<usize> = circuits.iter().map(|c| c.len()).collect();
    let result = (0..3).map(|_| heap.pop().unwrap()).product::<usize>();
    Ok(result)
}

#[cfg(test)]
mod tests {
    // Unit tests below
    #[test]
    fn test_solve_part() {
        let input = "162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689";

        assert_eq!(super::solve_part(input, 10).unwrap(), 40);
    }
}
