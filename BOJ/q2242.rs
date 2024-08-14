use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut sum = 0;
    let mut arr: Vec<i32> = vec![];
    for _ in 0..n {
        let a: i32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        sum += a;
        arr.push(a);        
    }
    let mut dp: Vec<Vec<bool>> = vec![vec![false; 801]; 801];
    let half = (sum / 2) as usize;
    dp[0][0] = true;
    for &a in &arr {
        let a = a as usize;
        for j in (0..=half).rev() {
            for k in (0..=j).rev() {
                if j >= a && dp[j - a][k] || k >= a && dp[j][k - a] {
                    dp[j][k] = true;
                }
            }
        }
    }
    let mut ret = -1;
    for a in 0..=half {
        for b in 0..=half {
            if !dp[a][b] { continue; }
            let c = sum as usize - a - b;
            if c > half { continue; }
            let s = sum as f64 / 2.0;
            let sq = s * (s - a as f64) * (s - b as f64) * (s - c as f64);
            let cur = (sq.sqrt() * 100.0) as i32;
            ret = max(ret, cur);
        }
    }
    println!("{}", ret);
}