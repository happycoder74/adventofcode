use crate::types::AocReturn;

pub fn report(part: &str, result: AocReturn) {
    println!("{}: {:<10}{:>20?}", part, result.result, result.duration);
}
