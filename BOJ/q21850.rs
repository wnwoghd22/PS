use std::io::{self, BufRead};
use std::cmp::min;

const INF: i64 = 1_000_000_000;

/// algorithm: DP
/// dp[u][0]: min cost making all nodes of subtree 0
/// dp[u][1]: min cost making nodes of subtree 0 except self
/// dp[u][2]: min cost making all nodes of subtree 0 with toggling self
/// dp[u][3]: min cost making nodes of subtree 0 excpet self, with toggling self
fn dfs(u: usize, p: usize, g: &Vec<Vec<usize>>, dp: &mut Vec<Vec<i64>>, b: &Vec<i32>) {
    let on = b[u - 1] as usize;
    dp[u][on] = 0; // self. no toggle is enough
    dp[u][on ^ 1] = INF; // toggled. IMPOSSIBLE
    dp[u][2 + on] = INF; // self. IMPOSSIBLE
    dp[u][2 + on ^ 1] = 1; // toggled. one toggling is enouugh
    for &v in &g[u] {
        if v == p { continue; }
        dfs(v, u, g, dp, b);

        let (x0, x1, x2, x3) = (dp[u][0], dp[u][1], dp[u][2], dp[u][3]);
        // let x0 = dp[u][0];
        // let x1 = dp[u][1];
        // let x2 = dp[u][2];
        // let x3 = dp[u][3];
        dp[u][0] = min(x0 + dp[v][0], x1 + dp[v][2]);
        dp[u][1] = min(x0 + dp[v][2], x1 + dp[v][0]);
        dp[u][2] = min(x2 + dp[v][1], x3 + dp[v][3]);
        dp[u][3] = min(x2 + dp[v][3], x3 + dp[v][1]);
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines().map(|x| x.unwrap());
    let n: usize = iter.next().unwrap().trim().parse().unwrap();
    let mut g: Vec<Vec<usize>> = vec![vec![]; n + 1];
    let mut dp: Vec<Vec<i64>> = vec![vec![0, 0, 0, 0]; n + 1];
    for _ in 0..n-1 {
        let e: Vec<usize> = iter.next().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        g[e[0]].push(e[1]);
        g[e[1]].push(e[0]);
    }
    let mut v: Vec<i32> = iter.next().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();

    dfs(1, 0, &g, &mut dp, &mut v);
    let ret = min(dp[1][0], dp[1][2]);
    if ret > n as i64 { println!("impossible"); }
    else { println!("{}", ret); }
}