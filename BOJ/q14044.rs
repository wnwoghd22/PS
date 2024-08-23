use std::io::{self, BufRead};

fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>, pho: &Vec<bool>) -> u32 {
    let mut ret = 0;
    for &v in &g[u] {
        if v == p { continue; }
        ret += dfs(v, u, g, pho);
    }
    if ret > 0 {
        ret + 2
    } else if pho[u] {
        2
    } else {
        0
    }
}

fn get_far(u: usize, p: usize, g: &Vec<Vec<usize>>, d: &mut Vec<u32>, pho: &Vec<bool>) -> Option<usize> {
    d[u] = d[p] + 1;
    let mut ret = u;
    for &v in &g[u] {
        if v == p { continue; }
        if let Some(x) = get_far(v, u, g, d, pho) {
            if d[x] > d[ret] {
                ret = x;
            }
        }
    }
    if pho[ret] {
        Some(ret)
    } else {
        None
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, _m) = (v[0], v[1]);

    let p: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut pho: Vec<bool> = vec![false; n];
    for i in p { pho[i] = true; }

    let mut g: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 1..n {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[v[0]].push(v[1]);
        g[v[1]].push(v[0]);
    }

    let mut d: Vec<u32> = vec![0; n];
    let x = get_far(0, 0, &g, &mut d, &pho).unwrap();
    let sum = dfs(x, n, &g, &pho) - 2;

    let y = get_far(x, x, &g, &mut d, &pho).unwrap();
    println!("{}", sum + d[x] - d[y]);
}