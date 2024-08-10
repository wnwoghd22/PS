use std::io::{self, BufRead};
use std::collections::HashMap;
use std::cmp::{min, max};

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

fn merge(i: usize, j: usize, uf: &mut DisjointSet, d: &mut Vec<i64>) {
    let di = d[uf.find(i)];
    let dj = d[uf.find(j)];
    if uf.join(i, j) {
        let x = uf.find(i);
        d[x] = min(di, dj);
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n = iter.next().unwrap().unwrap().trim().parse().unwrap();

    let mut arr: Vec<(i64, i64)> = vec![];
    let mut map: HashMap<i64, HashMap<i64, usize>> = HashMap::new();
    let mut dist: Vec<i64> = vec![0; n];
    for i in 0..n {
        let v: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        arr.push((v[0], v[1]));
        dist[i] = v[0].abs() + v[1].abs();
        if !map.contains_key(&v[0]) {
            map.insert(v[0], HashMap::new());
        }
        map.get_mut(&v[0]).unwrap().insert(v[1], i);
    }
    let mut uf = DisjointSet::new(n);
    for i in 0..n {
        if let Some(m) = map.get(&(arr[i].0 - 1)) {
            if let Some(&j) = m.get(&(arr[i].1 - 1)) { merge(i, j, &mut uf, &mut dist); }
            if let Some(&j) = m.get(&arr[i].1) { merge(i, j, &mut uf, &mut dist); }
            if let Some(&j) = m.get(&(arr[i].1 + 1)) { merge(i, j, &mut uf, &mut dist); }
        }
        if let Some(m) = map.get(&arr[i].0) {
            if let Some(&j) = m.get(&(arr[i].1 - 1)) { merge(i, j, &mut uf, &mut dist); }
            if let Some(&j) = m.get(&(arr[i].1 + 1)) { merge(i, j, &mut uf, &mut dist); }
        }
        if let Some(m) = map.get(&(arr[i].0 + 1)) {
            if let Some(&j) = m.get(&(arr[i].1 - 1)) { merge(i, j, &mut uf, &mut dist); }
            if let Some(&j) = m.get(&arr[i].1) { merge(i, j, &mut uf, &mut dist); }
            if let Some(&j) = m.get(&(arr[i].1 + 1)) { merge(i, j, &mut uf, &mut dist); }
        }
    }
    let mut sum = 0;
    let mut mx = 0;
    for i in 0..n {
        if uf.find(i) == i {
            sum += dist[i];
            mx = max(mx, dist[i]);
        }
    }
    println!("{}", sum * 2 - mx);
}