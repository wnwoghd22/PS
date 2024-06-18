use std::io::{self, BufRead};

struct Graph {
    edges: Vec<Vec<(usize, u32)>>,
}

impl Graph {
    fn query(&self, s: usize, e: usize) -> u32 {
        self.dfs(s, 0, 0, e).unwrap()
    }
    fn dfs(&self, u: usize, p: usize, d: u32, e: usize) -> Option<u32> {
        if u == e { return Some(d); }
        for (v, w) in &self.edges[u] {
            if *v == p { continue; }
            if let Some(x) = self.dfs(*v, u, d + w, e) {
                return Some(x);
            }
        }
        None
    }
}

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();

    let s = iter.next().unwrap().unwrap();
    let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();

    let n = v[0];
    let mut edges: Vec<Vec<(usize, u32)>> = vec![vec![]; n+1];
    for _ in 0..n-1 {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        edges[v[0]].push((v[1], v[2] as u32));
        edges[v[1]].push((v[0], v[2] as u32));
    }
    let g = Graph { edges };
    let m = v[1];
    for _ in 0..m {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        println!("{}", g.query(v[0], v[1]));
    }
}