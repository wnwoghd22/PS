use std::io::{self, BufRead};

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
    let n: usize = iterator.next().unwrap().unwrap().parse().unwrap();
    let mut uf = DisjointSet::new(n + 1);

    let mut v: Vec<Vec<i32>> = vec![];

    for _ in 0..n {
        let s = iterator.next().unwrap().unwrap();
        let rect: Vec<i32> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        v.push(rect);
    }

    for i in 0..n {
        if (v[i][0] == 0 || v[i][2] == 0) && v[i][1] <= 0 && v[i][3] >= 0 { 
            uf.join(i, n);
        }
        if (v[i][1] == 0 || v[i][3] == 0) && v[i][0] <= 0 && v[i][2] >= 0 { 
            uf.join(i, n);
        }
        for j in i+1..n {
            if v[j][0] > v[i][2] || v[i][0] > v[j][2] { continue; }
            if v[j][1] > v[i][3] || v[i][1] > v[j][3] { continue; }
            if v[j][0] < v[i][0] && v[i][2] < v[j][2]
                && v[j][1] < v[i][1] && v[i][3] < v[j][3] {
                continue;
            }
            if v[i][0] < v[j][0] && v[j][2] < v[i][2]
                && v[i][1] < v[j][1] && v[j][3] < v[i][3] {
                continue;
            }

            uf.join(i, j);
        }
    }

    let mut ret = 0;
    for i in 0..n+1 {
        if uf.find(i) == i {
            ret += 1;
        }
    }

    println!("{}", ret - 1);
}