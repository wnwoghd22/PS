use std::io;
use std::cmp::max;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: usize = s.trim().parse().unwrap();

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let a: Vec<i32> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut ret = -1_000_000_000;
    let mut dp: Vec<Vec<i32>> = vec![vec![-1_000_000_000; 2]; n + 1];
    for i in 0..n {
        dp[i + 1][0] = max(0, dp[i][0]) + a[i];
        dp[i + 1][1] = max(dp[i][0], dp[i][1] + a[i]);
        ret = max(ret, max(dp[i + 1][0], dp[i + 1][1]));
    }
    println!("{}", ret);
}