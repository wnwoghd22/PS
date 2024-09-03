use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let w: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let h: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();

    let mut dp: Vec<Vec<i32>> = w.iter().map(|&x| vec![0, x]).collect();
    for v in (1..n).rev() {
        let u = h[(v - 1) * 2];
        match h[v * 2 - 1] {
            0 => {
                dp[u][1] += dp[v][0];
                dp[u][0] += max(dp[v][0], dp[v][1]);
            },
            1 => {
                dp[u][1] = max(dp[u][0], dp[u][1]) + max(dp[v][0], dp[v][1]);
                dp[u][0] += dp[v][0];
            },
            2 => {
                dp[u][1] = max(dp[u][0] + dp[v][1], dp[u][1] + dp[v][0]);
                dp[u][0] += dp[v][0];
            },
            _ => (),
        }
    }
    println!("{}", max(dp[0][0], dp[0][1]));
}