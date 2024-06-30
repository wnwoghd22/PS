use std::io::{self, BufRead};

fn main() {
    let mut dp: Vec<Vec<u64>> = vec![vec![0; 10]; 64];
    let mut ret: Vec<u64> = vec![0; 64];
    for i in 0..10 { dp[0][i] = 1; }
    ret[0] = 10;
    for i in 1..64 {
        for j in 0..10 {
            for k in 0..j+1 {
                dp[i][j] += dp[i - 1][k];
            }
            ret[i] += dp[i][j];
        }
    }
    let mut iter = io::stdin().lock().lines();
    let tc: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..tc {
        let k: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        println!("{}", ret[k - 1]);
    }
}