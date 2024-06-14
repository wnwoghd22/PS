use std::io::{self, BufRead, Write};
use std::cmp::min;

struct MinSeg {
    t: Vec<i32>,
}

impl MinSeg {
    fn init_rec(&mut self, arr: &Vec<i32>, s: usize, e: usize, i: usize) {
        if s == e {
            self.t[i] = arr[s];
            return;
        }
        let m = s + e >> 1;
        self.init_rec(arr, s, m, i << 1); self.init_rec(arr, m + 1, e, i << 1 | 1);
        self.t[i] = min(self.t[i << 1], self.t[i << 1 | 1]);
    }

    fn init(arr: &Vec<i32>) -> Self {
        let mut seg = MinSeg {
            t: vec![0; arr.len() << 2],
        };
        seg.init_rec(arr, 1, arr.len() - 1, 1);
        seg
    }

    fn get(&self, l: usize, r: usize, s: usize, e: usize, i: usize) -> i32 {
        if r < s || e < l { return 1_000_000_007; }
        if l <= s && e <= r { return self.t[i]; }
        let m = s + e >> 1;
        return min(self.get(l, r, s, m, i << 1), self.get(l, r, m + 1, e, i << 1 | 1));
    }
}

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());
    
    let s = iterator.next().unwrap().unwrap();
    let v: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut a: Vec<i32> = vec![0];
    for _ in 0..v[0] {
        let x: i32 = iterator.next().unwrap().unwrap().parse().unwrap();
        a.push(x);
    }

    let tree = MinSeg::init(&a);

    for _ in 0..v[1] {
        let s = iterator.next().unwrap().unwrap();
        let q: Vec<usize> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        _ = writeln!(writer, "{}", tree.get(q[0], q[1], 1, v[0], 1));
    }
    writer.flush().unwrap();
}