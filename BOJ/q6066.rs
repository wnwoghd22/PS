use std::io;
use std::cmp::min;

static INF: usize = 1_000_000_007;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = v[0];
    let h = v[1];
    let mut dp: Vec<usize> = vec![INF; h + 5000];
    dp[0] = 0;
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        let p = v[0];
        let c = v[1];
        for i in p..dp.len() {
            dp[i] = min(dp[i], dp[i - p] + c);
        }
    }
    let mut ret = INF;
    for i in h..dp.len() {
        ret = min(ret, dp[i]);
    }
    println!("{}", ret);
}