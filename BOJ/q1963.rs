use std::io;
use std::collections::VecDeque;

static LEN: usize = 10000;

fn main() {
    let mut p: Vec<bool> = vec![false; LEN];
    for i in 2..LEN {
        if p[i] { continue; }
        for j in (i*2..LEN).step_by(i) {
            p[j] = true; 
        }
    }
    let mut s = String ::new();
    io::stdin().read_line(&mut s).unwrap();
    let t: u32 = s.trim().parse().unwrap();
    for _ in 0..t {
        let mut ss = String ::new();
        io::stdin().read_line(&mut ss).unwrap();
        let v: Vec<usize> = ss
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        let mut d: Vec<u32> = vec![0; LEN];
        let s = v[0];
        let e = v[1];
        let mut q: VecDeque<usize> = VecDeque::new();
        d[s] = 1;
        q.push_back(s);
        while let Some(u) = q.pop_front() {
            if u == e { break; }
            let d1 = u % 10;
            let d2 = u % 100 - d1;
            let d3 = u % 1000 - d1 - d2;
            let d4 = u - d1 - d2 - d3;
            let dg: Vec<usize> = vec![d1, d2, d3, d4];
            let x: Vec<usize> = vec![1, 10, 100, 1000];
            for i in 0..4 {
                for j in (i/3)..10 {
                    let v = u - dg[i] + x[i] * j;
                    if p[v] { continue; }
                    if d[v] != 0 { continue; }
                    d[v] = d[u] + 1;
                    q.push_back(v);
                }
            }
        }

        if d[e] == 0 {
            println!("Impossible");
        } else {
            println!("{}", d[e] - 1);
        }
    }
}