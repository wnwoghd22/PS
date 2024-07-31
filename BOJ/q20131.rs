use std::io::{self, BufRead, Write};
use std::collections::{BinaryHeap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());

    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let arr: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut d: Vec<u32> = vec![1; n + 1];
    for a in &arr { d[*a] += 1; }
    let mut pq: BinaryHeap<usize> = BinaryHeap::new();
    let mut edges: Vec<(usize, usize)> = vec![];
    for i in 1..=n {
        if d[i] == 1 {
            pq.push(i);
        }
    }
    for a in &arr {
        if let Some(u) = pq.pop() {
            if *a > u { edges.push((u, *a)); }
            else { edges.push((*a, u)); }
            d[*a] -= 1;
            if d[*a] == 1 { pq.push(*a); }
        }
    }

    // println!("{}", pq.len());
    let u = pq.pop().unwrap();
    let v = pq.pop().unwrap();
    edges.push((v, u));

    edges.sort();
    for (u, v) in edges {
        _ = writeln!(writer, "{} {}", u, v);
    }
    writer.flush().unwrap();
}