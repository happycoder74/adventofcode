pub mod part1;
pub mod part2;

fn get_md5(input: &str) -> String {
    let digest = md5::compute(input.as_bytes());
    format!("{:x}", digest)
}
