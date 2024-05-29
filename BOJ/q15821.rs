use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();

    let s = iterator.next().unwrap().unwrap();
    let v: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, k] = v[..] else { panic! (); };

    let mut dist: Vec<i64> = vec![];
    for _ in 0..n {
        let p: usize = iterator.next().unwrap().unwrap().parse().unwrap();
        let s = iterator.next().unwrap().unwrap();
        let v: Vec<i64> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let mut d: i64 = 0;
        for i in 0..p {
            let cur = v[i * 2] * v[i * 2] + v[i * 2 + 1] * v[i * 2 + 1];
            if cur > d { d = cur; }
        }
        dist.push(d);
    }
    dist.sort();
    println!("{}.00", dist[k - 1]);
}