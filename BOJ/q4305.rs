use std::io::{self, BufRead, Write};
use std::collections::VecDeque;

fn solve(g: &Vec<Vec<bool>>) -> Vec<Vec<usize>> {
    let mut adj: Vec<Vec<bool>> = vec![vec![false; 26]; 26];
    for i in 0..26 {
        let mut visited: Vec<bool> = vec![false; 26];
        let mut q: VecDeque<usize> = VecDeque::new();
        q.push_back(i);
        visited[i] = true;
        while let Some(u) = q.pop_front() {
            adj[i][u] = true;
            for v in 0..26 {
                if !visited[v] && g[u][v] {
                    visited[v] = true;
                    q.push_back(v);
                }
            }
        }
    }
    let mut ret: Vec<Vec<usize>> = vec![vec![]; 26];
    let mut checked: Vec<bool> = vec![false; 26];
    for u in 0..26 {
        if checked[u] { continue; }
        for v in u..26 {
            if adj[u][v] && adj[v][u] {
                checked[v] = true;
                ret[u].push(v);
            }
        }
    }
    ret
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());

    'testcase: 
    loop {
        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        if n == 0 { break 'testcase; }

        let mut g: Vec<Vec<bool>> = vec![vec![false; 26]; 26];
        let mut valid: Vec<bool> = vec![false; 26];
        for _ in 0..n {
            let v: Vec<u8> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.chars().next().unwrap() as u8).collect();
            for i in 0..5 {
                valid[(v[i] - b'A') as usize] = true;
                if v[i] == v[5] { continue; }
                g[(v[i] - b'A') as usize][(v[5] - b'A') as usize] = true;
            }
        }
        let ret = solve(&g);
        for u in 0..26 {
            if !valid[u] { continue; }
            for &e in &ret[u] {
                _ = write!(writer, "{} ", (e as u8 + b'A') as char);
            }
            _ = writeln!(writer);
        }   
        _ = writeln!(writer);
    }
    writer.flush().unwrap();
}