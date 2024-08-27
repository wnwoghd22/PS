use std::io::{self, BufRead, Write};
use std::collections::{HashSet};
use std::cmp::min;

fn dfs(
    u: usize, // current node
    g: &Vec<Vec<usize>>, // graph
    ord: &mut Vec<usize>, // euler tour order
    idx: &mut usize,
    st: &mut Vec<usize>,
    checked: &mut Vec<bool>,
    scc: &mut Vec<Vec<usize>>
) -> usize {
    *idx += 1;
    ord[u] = *idx;
    let mut parent = ord[u];
    st.push(u);

    for &v in &g[u] {
        if ord[v] == 0 {
            parent = min(parent, dfs(v, g, ord, idx, st, checked, scc));
        } else if !checked[v] {
            parent = min(parent, ord[v]);
        }
    }

    if parent == ord[u] {
        let mut comp = Vec::new();
        while let Some(e) = st.pop() {
            comp.push(e);
            checked[e] = true;
            if e == u {
                break;
            }
        }
        scc.push(comp);
    }
    parent
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, m) = (v[0], v[1]);

    let mut g: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[v[0]].push(v[1]);        
    }

    let mut ord = vec![0; n + 1];
    let mut checked = vec![false; n + 1];
    let mut scc = vec![];
    let mut st = vec![];
    let mut idx = 0;
    for u in 1..=n {
        if !checked[u] {
            dfs(u, &g, &mut ord, &mut idx, &mut st, &mut checked, &mut scc);
        }
    }
    let mut group = vec![0; n + 1];
    let mut g_scc: Vec<HashSet<usize>> = vec![HashSet::new(); scc.len()];
    let mut incoming = vec![0; scc.len()];
    for (i, comp) in scc.iter().enumerate() {
        for &e in comp {
            group[e] = i;
        }
    }
    for u in 1..=n {
        for &v in &g[u] {
            let u = group[u];
            let v = group[v];
            if u != v && !g_scc[u].contains(&v) {
                g_scc[u].insert(v);
                incoming[v] += 1;
            }
        }
    }
    let mut result = 0;
    let mut start = 0;
    for i in 0..scc.len() {
        if incoming[i] == 0 {
            result += 1;
            start = i;
        }
    }
    if result > 1 {
        _ = write!(writer, "0");
    } else {
        _ = writeln!(writer, "{}", scc[start].len());
        scc[start].sort();
        for e in &scc[start] {
            _ = write!(writer, "{} ", e);
        }
    }
    writer.flush().unwrap();
}