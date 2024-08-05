use std::io::{self, BufRead, Write};

fn dfs(u: usize, g: &Vec<Vec<usize>>, d: &mut Vec<usize>, sz: &mut Vec<usize>) {
    sz[u] = 1;
    for v in &g[u] {
        d[*v] = d[u] + 1;
        dfs(*v, g, d, sz);
        sz[u] += sz[*v];
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());

    let tc: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for t in 0..tc {
        if t != 0 { _ = write!(writer, "\n"); }
        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let n = 1 << n;
        let mut arr: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let queries: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let mut v: Vec<usize> = vec![0];
        while let Some(x) = arr.pop() { v.push(x); }
        for i in (1..=n).rev() { v.push(i); }

        let mut g: Vec<Vec<usize>> = vec![vec![]; n + 1];
        for i in 1..n {
            let l = v[i << 1];
            let r = v[i << 1 | 1];
            if l == v[i] { g[l].push(r); }
            if r == v[i] { g[r].push(l); }
        }

        let mut d: Vec<usize> = vec![0; n + 1];
        let mut sz: Vec<usize> = vec![0; n + 1];
        dfs(v[1], &g, &mut d, &mut sz);

        for u in &queries[1..] {
            _ = writeln!(writer, "Player {} can be ranked as high as {} or as row as {}.",
                *u,
                d[*u] + 1,
                n - sz[*u] + 1,
            );
        }
    }
    writer.flush().unwrap();
}