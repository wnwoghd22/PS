use std::io::{self, BufRead};
use std::cmp::{max};

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();

    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut dp: Vec<u32> = vec![0; n + 1];
    let mut ret = 0;

    for u in 1..n+1 {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<usize> = s
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let mut pre = 0;
        for p in &v[2..] {
            pre = max(pre, dp[*p]);
        }
        dp[u] = pre + v[0] as u32;
        ret = max(ret ,dp[u]);
    }
    println!("{}", ret);
}
