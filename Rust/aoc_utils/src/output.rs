use crate::AocReturn;

pub fn report(result: AocReturn) {
    print!("Part 1: ");
    match result.part1 {
        Ok(x) => println!("{:<10}{:>20?}", x.result, x.duration),
        Err(e) => println!("{}", e),
    };
    print!("Part 2: ");
    match result.part2 {
        Ok(x) => println!("{:<10}{:>20?}", x.result, x.duration),
        Err(e) => println!("{}", e),
    };
}
