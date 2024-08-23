use std::io::{self, BufRead, Write};
use std::collections::{BinaryHeap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let t: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let p: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let s: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        
        let mut l: Vec<usize> = vec![0; n];
        let mut r: Vec<usize> = vec![0; n];
        for i in 0..n {
            l[i] = i;
            r[i] = i + 2;
        }

        let mut ret: Vec<i64> = vec![0; n];
        let mut pq: BinaryHeap<(i64, usize, usize)> = BinaryHeap::new();
        for i in 0..n-1 {
            let d = p[i + 1] - p[i];
            let v = s[i] + s[i + 1];
            let x = 2 * ((d + v - 1) / v) - (!i % 2) as i64;
            pq.push((-x, i, i + 1));
        }

        while let Some((x, a, b)) = pq.pop() {
            if ret[a] != 0 || ret[b] != 0 { continue; }
            ret[a] = -x; ret[b] = -x;
            let a = l[a];
            let b = r[b];
            if a != 0 && b != n + 1 {
                let i = a - 1;
                let j = b - 1;
                r[i] = b;
                l[j] = a;
                let d = p[j] - p[i];
                let v = s[i] + s[j];
                let x = 2 * ((d + v - 1) / v) - (!i % 2) as i64;
                pq.push((-x, i, j));
            }
        }
        for i in 0..n {
            _ = write!(writer, "{} ", ret[i]);
        }
        _ = writeln!(writer);
    }
}