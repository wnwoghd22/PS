use std::io;
use std::cmp::min;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, _m] = values[..] else { panic!(); };
    let mut dp = vec![vec![-1; n + 1]; n + 1];
    let mut days = vec![false; n + 1];

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let values: Vec<usize> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    for d in values {
        days[d] = true;
    }

    dp[0][0] = 0;
    for d in 1..n + 1 {
        for c in 0..n {
            if days[d] {
                dp[d][c] = dp[d - 1][c];
            }
            if c + 3 <= n && dp[d - 1][c + 3] != -1 { // use coupons
                if dp[d][c] == -1 { dp[d][c] = dp[d - 1][c + 3]; }
                else { dp[d][c] = min(dp[d][c], dp[d - 1][c + 3]); }
            }
            if dp[d - 1][c] != -1 { // one-day ticket
                if dp[d][c] == -1 { dp[d][c] = dp[d - 1][c] + 10000; }
                else { dp[d][c] = min(dp[d][c], dp[d - 1][c] + 10000); }
            }
            if d >= 3 && c >= 1 && dp[d - 3][c - 1] != -1 { // three days ticket
                if dp[d][c] == -1 { dp[d][c] = dp[d - 3][c - 1] + 25000; }
                else { dp[d][c] = min(dp[d][c], dp[d - 3][c - 1] + 25000); }
            }
            if d >= 5 && c >= 2 && dp[d - 5][c - 2] != -1 { // five days ticket
                if dp[d][c] == -1 { dp[d][c] = dp[d - 5][c - 2] + 37000; }
                else { dp[d][c] = min(dp[d][c], dp[d - 5][c - 2] + 37000); }
            }
        }
    }

    let mut ret = 1000000000;
    for cost in &dp[n] {
        if *cost != -1 {
            ret = min(ret, *cost);
        }
    }
    println!("{}", ret);
}