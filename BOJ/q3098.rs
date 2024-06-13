use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
        
    let [n, m] = v[..] else { panic!(); };
    
    let mut g: Vec<Vec<bool>> = vec![vec![false; n + 1]; n + 1];
    for _ in 0..m {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<usize> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
            
        let [a, b] = v[..] else { panic!(); };
        g[a][b] = true;
        g[b][a] = true;
    }
    
    let mut cnt = m;
    let max = n * (n - 1) / 2;
    let mut history: Vec<usize> = vec![];
    while cnt < max { // n^5
        let mut now = 0;
        let mut cur: Vec<Vec<bool>> = vec![vec![false; n + 1]; n + 1];
        for i in 1..n+1 {
            for j in 1..n+1 {
                cur[i][j] = g[i][j];
            }
        }
        for u in 1..n+1 {
            for p in 1..n+1 {
                if p == u { continue; }
                if g[u][p] {
                    cur[u][p] = true;
                    for v in 1..n+1 {
                        if v == u { continue; }
                        if g[p][v] && !cur[u][v] {
                            cur[u][v] = true;
                            cur[v][u] = true;
                            now += 1;
                        }
                    }
                }
            }
        }
        history.push(now);
        cnt += now;
        g = cur;
    }
    println!("{}", history.len());
    for c in history {
        println!("{}", c);
    }
}