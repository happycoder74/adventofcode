use aoc_2017::mod_2017_02;

use criterion::{criterion_group, criterion_main, Criterion};

fn criterion_benchmark(c: &mut Criterion) {
    let input = aoc_utils::get_input(2017, 2, false);
    let parsed = aoc_2017::mod_2017_02::parse_input(&input);
    c.bench_function("2017-02-1", |b| {
        b.iter(|| mod_2017_02::solve_part_1(&parsed))
    });
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
