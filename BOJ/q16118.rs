use std::io;
use std::collections::BinaryHeap;
use std::cmp::min;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m] = v[..] else { panic!(); };
    let mut g: Vec<Vec<(usize, i32)>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<usize> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        g[v[0]].push((v[1], v[2] as i32));
        g[v[1]].push((v[0], v[2] as i32));
    }
    let mut pq: BinaryHeap<(i32, usize)> = BinaryHeap::new();
    let mut dp: Vec<i32> = vec![1_000_000_000; n + 1];
    dp[1] = 0;
    pq.push((0, 1));
    while let Some((d, u)) = pq.pop() {
        let d = -d;
        if dp[u] < d { continue; }
        for (v, w) in &g[u] {
            if d + w * 2 < dp[*v] {
                dp[*v] = d + w * 2;
                pq.push((-d - w * 2, *v));
            }
        }
    }

    let mut pq2: BinaryHeap<(i32, usize, usize)> = BinaryHeap::new();
    let mut dp2: Vec<Vec<i32>> = vec![vec![1_000_000_000; 2]; n + 1];
    dp2[1][0] = 0;
    pq2.push((0, 1, 0));
    while let Some((d, u, x)) = pq2.pop() {
        let d = -d;
        if dp2[u][x] < d { continue; }
        for (v, w) in &g[u] {
            if x == 0 {
                if d + w < dp2[*v][1] {
                    dp2[*v][1] = d + w;
                    pq2.push((-d - w, *v, 1));
                }
            }
            if x == 1 {
                if d + w * 4 < dp2[*v][0] {
                    dp2[*v][0] = d + w * 4;
                    pq2.push((-d - w * 4, *v, 0));
                }
            }
        }
    }

    let mut ret = 0;
    for i in 2..n+1 {
        println!("{} {}", dp[i], min(dp2[i][0], dp2[i][1]));
        if dp[i] < min(dp2[i][0], dp2[i][1]) {
            ret += 1;
        }
    }
    println!("{}", ret);
}