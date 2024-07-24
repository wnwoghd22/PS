use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut m: Vec<Vec<i32>> = vec![];
    let mut p: Vec<Vec<i32>> = vec![vec![0; n+1];n+1];
    let mut dp: Vec<Vec<(i32, i32)>> = vec![vec![(0, 0); n+1]; n+1];

    for _ in 0..n {
        let v: Vec<i32> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        m.push(v);
    }
    
    let k: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..k {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        p[v[0]][v[1]] = 1;
    }

    for i in 1..=n {
        for j in 1..=n {
            let (a1, a2) = if dp[i-1][j].0 > dp[i][j-1].0 {
                dp[i-1][j]
            } else if dp[i-1][j].0 < dp[i][j-1].0 {
                dp[i][j-1]
            } else {
                (dp[i-1][j].0, max(dp[i-1][j].1, dp[i][j-1].1))
            };
            dp[i][j] = (a1 + m[i-1][j-1], a2 + p[i][j]);
        }
    }
    println!("{} {}", dp[n][n].0, dp[n][n].1);
}