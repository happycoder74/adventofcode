
pub fn report<T: std::fmt::Display>(part: &str, result: (T, std::time::Duration)) {
    println!("{}: {:<10}{:>20?}", part, result.0, result.1);
}
