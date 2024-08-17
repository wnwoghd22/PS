use std::io::{self, BufRead, Write};
use std::cmp::max;

const INF: i64 = 1e12 as i64;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut pivot = [-INF; 8];
    let mut pos: Vec<Vec<i64>> = vec![];
    for _ in 0..n {
        let p: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        for i in 0..8 {
            let mut x = 0;
            for j in 0..3 {
                if i & 1 << j == 0 {
                    x += p[j];
                } else {
                    x -= p[j];
                }
            }
            pivot[i] = max(pivot[i], x);
        }
        pos.push(p);
    }
    for k in 0..n {
        let mut ret = -INF;
        for i in 0..8 {
            let mut x = pivot[i];
            for j in 0..3 {
                if i & 1 << j == 0 {
                    x -= pos[k][j];
                } else {
                    x += pos[k][j];
                }
            }
            ret = max(ret, x);
        }
        _ = writeln!(writer, "{}", ret);
    }
}