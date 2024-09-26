use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (x, t, m, v, n) = (v[0], v[1], v[2], v[3], v[4]);
    if x * m > m * v * t {
       println!("-1");
    } else {
        let mut dp: Vec<i32> = vec![0; m * v * t - x * m + 1];
        for _ in 0..n {
            let v: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            let (w, c) = (v[0] * v[1], v[2] as i32);
            for i in (w..dp.len()).rev() {
                dp[i] = max(dp[i], dp[i - w] + c);
            }
        }
        println!("{}", dp[dp.len() - 1]);
    }
}