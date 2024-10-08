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
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    
    let mut uf = DisjointSet::new(n);
    let mut pq: BinaryHeap<(i32, usize, usize)> = BinaryHeap::new();

    for i in 0..n {
        let d: i32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        pq.push((-d, i, n));
    }
    for i in 0..n {
        let v: Vec<i32> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        for j in 0..n {
            if i == j { continue; }
            pq.push((-v[j], i, j));
        }
    }

    let mut ret = 0;
    while let Some((w, u, v)) = pq.pop() {
        let w = -w;
        if uf.join(u, v) {
            ret += w;
        }
    }
    println!("{}", ret);
}