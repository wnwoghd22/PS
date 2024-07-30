use std::io::{self, BufRead, Write};

fn dfs(u: usize, k: usize, c: &mut Vec<usize>, g: &Vec<Vec<usize>>) {
    let mut b = 0;
    for v in &g[u] { b |= 1 << c[*v]; }
    if b & 2 != 0 && b & 1 << k == 0 { c[u] = k; }
    else {
        for i in 2..=k {
            if b & 1 << i != 0 && b & 1 << (i - 1) == 0 {
                c[u] = i - 1;
                break;
            }
        }
    }
    for v in &g[u] {
        if c[*v] == 0 {
            dfs(*v, k, c, g);
        }
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let [n, k, m] = v[..] else { panic!() };
    
    let mut c = vec![0; n + 1];
    let mut g = vec![vec![]; n + 1];
    for _ in 0..m {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[v[0]].push(v[1]);
        g[v[1]].push(v[0]);
    }
    for i in 1..=k { c[i] = i; }
    for i in 1..=k {
        for u in &g[i] {
            if c[*u] == 0 {
                dfs(*u, k, &mut c, &g);
            }
        }
    }
    for i in 1..=n {
        _ = write!(writer, "{} ", c[i]);
    }
    writer.flush().unwrap();
}