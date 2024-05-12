use std::io;
use std::cmp::max;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, k] = values[..] else {panic!();};
    let mut dp: Vec<Vec<i64>> = vec![vec![-1; k + 1]; 2];
    dp[0][0] = 0;
    for i in 0..n {
        dp[!i & 1] = vec![-1; k + 1];
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let values: Vec<usize> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [t1, c1, t2, c2] = values[..] else {panic!{};};
        for j in (t1..k+1).rev() {
            if dp[i & 1][j - t1] != -1 {
                dp[!i & 1][j] = max(dp[!i & 1][j], dp[i & 1][j - t1] + c1 as i64);
            }
        }
        for j in (t2..k+1).rev() {
            if dp[i & 1][j - t2] != -1 {
                dp[!i & 1][j] = max(dp[!i & 1][j], dp[i & 1][j - t2] + c2 as i64);
            }
        }
    }
    let mut ret = 0;
    for c in &dp[n & 1] {
        ret = max(ret, *c);
    }
    println!("{}", ret);
}