use std::io::{self, BufRead};
use std::collections::BinaryHeap;

struct DisjointSet {
    _size: usize,
    v: Vec<i32>,
}

impl DisjointSet {
    fn new(size: usize) -> Self {
        let v: Vec<i32> = vec![-1; size + 1];
        DisjointSet {
            _size: size,
            v,
        }
    }

    fn find(&mut self, i: usize) -> usize {
        if self.v[i] < 0 {
            i
        } else {
            self.v[i] = self.find(self.v[i] as usize) as i32;
            self.v[i] as usize
        }
    }

    fn join(&mut self, i: usize, j: usize) -> bool {
        let i = self.find(i);
        let j = self.find(j);
        if i == j { return false; }
        if self.v[i] < self.v[j] {
            self.v[i] += self.v[j];
            self.v[j] = i as i32;
        } else {
            self.v[j] += self.v[i];
            self.v[i] = j as i32;
        }
        true
    }
}

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    let s = iterator.next().unwrap().unwrap();
    let v: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m, t] = v[..] else { panic! (); };

    let mut uf = DisjointSet::new(n);
    let mut pq: BinaryHeap<(i32, usize, usize)> = BinaryHeap::new();

    for _ in 0..m {
        let s = iterator.next().unwrap().unwrap();
        let v: Vec<usize> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [a, b, c] = v[..] else { panic! (); };
        pq.push((-(c as i32), a, b));
    }

    let mut ret = (t * (n - 1) * (n - 2) / 2) as i32;
    while let Some((w, u, v)) = pq.pop() {
        let w = -w;
        if uf.join(u, v) {
            ret += w;
        }
    }
    println!("{}", ret);
}