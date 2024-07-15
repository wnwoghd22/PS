use std::io::{self, BufRead};
use std::collections::BinaryHeap;
use std::cmp::min;

static INF: i64 = 1_000_000_000_000_000;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let [n, k, l] = v[..] else { panic!(); };

    let mut s = vec![];
    for _ in 0..n {
        let si: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        s.push(si);
    }

    let mut g: Vec<Vec<(usize, i64)>> = vec![vec![]; k + 1];
    for _ in 0..l {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[v[0]].push((v[1], v[2] as i64));
        g[v[1]].push((v[0], v[2] as i64));
    }

    let mut ret = INF;
    for b in 0..17 {
        let mut pq: BinaryHeap<(i64, usize)> = BinaryHeap::new();
        let mut dp: Vec<i64> = vec![INF; k + 1];

        for u in 0..n {
            if (u & 1 << b) == 0 {
                dp[s[u]] = 0;
                pq.push((0, s[u]));
            } 
        }

        while let Some((d, u)) = pq.pop() {
            let d = -d;
            if dp[u] < d { continue; }
            for (v, w) in &g[u] {
                if d + w < dp[*v] {
                    dp[*v] = d + w;
                    pq.push((-d - w, *v));
                }
            }
        }

        for u in 0..n {
            if (!u & 1 << b) == 0 {
                ret = min(ret, dp[s[u]]);
            } 
        }
    }
    println!("{}", ret * 3);
}