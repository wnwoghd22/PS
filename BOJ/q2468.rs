use std::io::{self, BufRead};
use std::cmp::max;

const DELTA: [(i32, i32); 4] = [(-1, 0), (0, 1), (1, 0), (0, -1)];

fn adjacent(x: usize, y: usize, dx: i32, dy: i32, n: usize, m: usize) -> Option<(usize, usize)> {
    if x == 0 && dx == -1 { return None; }
    if y == 0 && dy == -1 { return None; }
    let x = (x as i32 + dx) as usize;
    let y = (y as i32 + dy) as usize;
    if x < n && y < m {
        Some((x, y))
    } else {
        None
    }
}

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
    let mut map: Vec<Vec<usize>> = vec![];
    let mut uf = DisjointSet::new(n * n);
    let mut arr: Vec<Vec<(usize, usize)>> = vec![vec![]; 101];
    for i in 0..n {
        let row: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        for j in 0..n {
            arr[row[j]].push((i, j));
        }
        map.push(row);
    }

    let mut ret = 0;
    let mut cur = 0;
    for h in (1..101).rev() {
        for (x, y) in &arr[h] {
            cur += 1;
            for (dx, dy) in DELTA {
                if let Some((nx, ny)) = adjacent(*x, *y, dx, dy, n, n) {
                    if map[nx][ny] >= h && uf.join(*x * n + *y, nx * n + ny) {
                        cur -= 1;
                    }
                }
            }
        }
        ret = max(ret, cur);
    }
    println!("{}", ret);
}