use std::io;

static MOD: u64 = 1_000_000_000;

fn main() {
    let mut dp: Vec<Vec<u64>> = vec![vec![0; 201]; 201];

    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let (N, K) = (values[0], values[1]);

    dp[0][0] = 1;
    for n in 0..N + 1 {
        for k in 1..K + 1 {
            for m in 0..n + 1 {
                dp[n][k] += dp[m][k - 1];
                dp[n][k] %= MOD;
            }
        }
    }
    println!("{}", dp[N][K]);
}