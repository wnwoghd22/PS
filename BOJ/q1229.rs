use std::io;
use std::cmp::min;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: usize = s.trim().parse().unwrap();

    let mut dp: Vec<usize> = vec![0; n + 1];
    for i in 1..n+1 {
        let mut k = 1;
        let mut d = 1;
        dp[i] = i;
        while k <= i {
            dp[i] = min(dp[i], dp[i - k] + 1);
            d += 4; k += d;
        }
    }
    println!("{}", dp[n]);
}