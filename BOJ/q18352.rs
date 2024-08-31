use std::io::{self, BufRead};
use std::collections::VecDeque;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, m, k, x) = (v[0], v[1], v[2] as i32, v[3]);
    let mut g: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[v[0]].push(v[1]);
    }
    let mut dist: Vec<i32> = vec![-1; n + 1];
    let mut q: VecDeque<usize> = VecDeque::new();
    let mut cnt = 0;
    q.push_back(x);
    dist[x] = 0;
    while let Some(u) = q.pop_front() {
        if dist[u] == k { cnt += 1; }
        for &v in &g[u] {
            if dist[v] == -1 {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    if cnt == 0 { println!("-1"); }
    else {
        for u in 1..=n {
            if dist[u] == k {
                println!("{}", u);
            }
        }
    }
}