use std::io::{self, BufRead};
use std::collections::BinaryHeap;

struct Network {
    n: usize,
    edges: Vec<Vec<(usize, i32)>>,
}

impl Network {
    fn simulate(&self, c: usize) -> (u32, i32) {
        let mut pq: BinaryHeap<(i32, usize)> = BinaryHeap::new();
        let mut dp = vec![1_000_000_000; self.n + 1];

        pq.push((0, c));
        dp[c] = 0;
        let mut cnt = 0;
        let mut dist = 0;

        while let Some((d, i)) = pq.pop() {
            let d = -d;
            if d > dp[i] {
                continue;
            }
            cnt += 1;
            dist = d;
            for (j, w) in &self.edges[i] {
                if d + *w < dp[*j] {
                    dp[*j] = d + *w;
                    pq.push((-dp[*j], *j));
                }
            }
        }

        (cnt, dist)
    }
}

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    let tc: u32 = iterator.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..tc {
        let s = iterator.next().unwrap().unwrap();
        let v: Vec<usize> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [n, d, c] = v[..] else { panic! (); };
        
        let mut edges: Vec<Vec<_>> = vec![vec![]; n + 1];
        for _ in 0..d {
            let s = iterator.next().unwrap().unwrap();
            let v: Vec<usize> = s
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();
            let [a, b, s] = v[..] else { panic! (); };
            edges[b].push((a, s as i32));
        }
        let network = Network {
            n,
            edges,
        };
        let (cnt, dist) = network.simulate(c);
        println!("{} {}", cnt, dist);
    }
}