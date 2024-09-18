use std::io::{self, BufRead};
use std::collections::{VecDeque, HashMap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut adj: Vec<Vec<bool>> = vec![vec![false; n * 25]; n * 25];
    let mut map: HashMap<String, usize> = HashMap::new();
    let mut g: Vec<Vec<usize>> = vec![vec![]; n * 25];
    let mut idx: usize = 0;
    for _ in 0..n {
        let input = iter.next().unwrap().unwrap();
        let v: Vec<&str> = input.split_whitespace().collect();
        if !map.contains_key(v[0]) { map.insert(v[0].to_string(), idx); idx += 1; }

        for &w in &v[2..] {
            if !map.contains_key(w) { map.insert(w.to_string(), idx); idx += 1; }
            g[map[w]].push(map[v[0]]);
        }
    }
    let s: usize = map[&iter.next().unwrap().unwrap()];

    for x in 0..idx {
        let mut q: VecDeque<usize> = VecDeque::new();
        let mut c: Vec<bool> = vec![false; idx];
        c[x] = true;
        q.push_back(x);
        while let Some(u) = q.pop_front() {
            for &v in &g[u] {
                if !c[v] {
                    c[v] = true;
                    adj[x][v] = true;
                    q.push_back(v);
                }
            }
        }
    }
    let mut incoming: Vec<i32> = vec![0; idx];
    let mut dp: Vec<i128> = vec![1; idx];
    let mut q: VecDeque<usize> = VecDeque::new();
    for u in 0..idx {
        for &v in &g[u] {
            if adj[u][v] && adj[v][u] { continue; }
            incoming[v] += 1;
        }
    }
    for u in 0..idx {
        if incoming[u] == 0 {
            q.push_back(u);
        }
    }
    while let Some(u) = q.pop_front() {
        // println!("{}", u);
        for &v in &g[u] {
            if adj[u][v] && adj[v][u] { continue; }
            dp[v] += dp[u];
            incoming[v] -= 1;
            if incoming[v] == 0 {
                q.push_back(v);
            }
        }
    }
    println!("{}", dp[s]);
}