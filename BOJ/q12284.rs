use std::io::{self, BufRead, Write};
use std::collections::BinaryHeap;
use std::collections::HashMap;

struct Network {
    n: usize,
    edges: Vec<Vec<(usize, i32)>>,
}

impl Network {
    fn dijkstra(&self, u: usize, v: usize) -> i32 {
        let mut pq: BinaryHeap<(i32, usize)> = BinaryHeap::new();
        let mut dp = vec![1_000_000_000; self.n + 1];

        pq.push((0, u));
        dp[u] = 0;

        while let Some((d, i)) = pq.pop() {
            let d = -d;
            if i == v { return d; }
            if d > dp[i] { continue; }
            for (j, w) in &self.edges[i] {
                if d + *w < dp[*j] {
                    dp[*j] = d + *w;
                    pq.push((-dp[*j], *j));
                }
            }
        }
        -1
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());

    let tc: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();

    for t in 1..=tc {
        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut map: HashMap<String, usize> = HashMap::new();
        let mut c: Vec<usize> = vec![0; n + 1];
        let mut idx = 0;
        for i in 1..=n {
            let key = iter.next().unwrap().unwrap();
            if !map.contains_key(&key) {
                idx += 1;
                map.insert(key.clone(), idx);
            }
            c[i] = map[&key];
        } 
        let m: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut edges: Vec<Vec<_>> = vec![vec![]; idx + 1];
        for _ in 0..m {
            let a: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            let (u, v, w) = (a[0], a[1], a[2] as i32);
            edges[c[u]].push((c[v], w));
        }
        let network = Network {
            n: idx,
            edges,
        };
        _  = writeln!(writer, "Case #{}:", t);
        let s: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        for _ in 0..s {
            let a: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            
        _  = writeln!(writer, "{}", network.dijkstra(c[a[0]], c[a[1]]));
        }
    }
    writer.flush().unwrap();
}