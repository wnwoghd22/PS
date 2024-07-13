use std::io::{self, BufRead};
use std::collections::VecDeque;
use std::cmp::{max, min};

static INF: u32 = 1_000_000_007;
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
    let dim: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut map: Vec<Vec<char>> = vec![];
    let mut dist: Vec<Vec<u32>> = vec![vec![INF; dim[1]]; dim[0]];
    let mut s = 0;
    let mut e = 0;
    let mut q: VecDeque<(usize, usize)> = VecDeque::new();
    for i in 0..dim[0] {
        let row: Vec<char> = iter.next().unwrap().unwrap().chars().collect();
        for j in 0..dim[1] {
            if row[j] == 'S' { s = i * dim[1] + j; }
            if row[j] == 'E' { e = i * dim[1] + j; }
            if row[j] == '*' {
                dist[i][j] = 0;
                q.push_back((i * dim[1] + j, i * dim[1] + j));
            }
        }
        map.push(row);
    }
    while let Some((x, y)) = q.pop_front() {
        let (r, c) = (x / dim[1], x % dim[1]);
        let (a, b) = (y / dim[1], y % dim[1]);
        for (dx, dy) in DELTA {
            if let Some((nx, ny)) = adjacent(r, c, dx, dy, dim[0], dim[1]) {
                let chevi_x = if nx > a { nx - a } else { a - nx };
                let chevi_y = if ny > b { ny - b } else { b - ny }; 
                let chevi = max(chevi_x, chevi_y) as u32;
                if dist[nx][ny] > chevi {
                    dist[nx][ny] = chevi;
                    q.push_back((nx * dim[1] + ny, y));
                }
            }
        }
    }
    let mut edges: Vec<(u32, usize, usize)> = vec![];
    for r in 0..dim[0] {
        for c in 0..dim[1] {
            if map[r][c] == '#' || map[r][c] == '*' { continue; }
            if r + 1 < dim[0] && map[r + 1][c] != '#' && map[r + 1][c] != '*' {
                edges.push((min(dist[r][c], dist[r + 1][c]), r * dim[1] + c, (r + 1) * dim[1] + c));
            }
            if c + 1 < dim[1] && map[r][c + 1] != '#' && map[r][c + 1] != '*' {
                edges.push((min(dist[r][c], dist[r][c + 1]), r * dim[1] + c, r * dim[1] + c + 1));
            }
        }
    }
    edges.sort();
    let mut uf = DisjointSet::new(dim[0] * dim[1]);
    for (d, u, v) in edges.iter().rev() {
        if uf.join(*u, *v) && uf.find(s) == uf.find(e) {
            if *d == INF {
                println!("safe");
            } else {
                println!("{}", d);
            }
            return;
        }
    }
    println!("-1");
}