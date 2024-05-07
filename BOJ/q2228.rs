use std::io;
use std::cmp::max;

static INF: i64 = 1e17 as i64;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let (n, m) = (values[0], values[1]);

    let mut sum = vec![0; n + 1];
    let mut arr: Vec<i64> = vec![0; n + 1];
    for i in 1..n + 1 {
        let mut x = String::new();
        io::stdin().read_line(&mut x).unwrap();
        arr[i] = x.trim().parse().unwrap();
        sum[i] = sum[i - 1] + arr[i];
    }

    let mut ret = -INF;
    let mut dp: Vec<Vec<i64>> = vec![vec![-INF; m + 1]; n + 1];
    dp[0][0] = 0;
    for i in 1..n + 1 {
        dp[i][1] = arr[i] + max(0, dp[i - 1][1]);
        for j in 1..m + 1 {
            if dp[i - 1][j] != -INF {
                dp[i][j] = arr[i] + dp[i - 1][j];
            }
            let mut range_max = arr[i];
            for k in (1..i).rev() {
                range_max = max(range_max, sum[i] - sum[k]);
                if dp[k - 1][j - 1] != -INF {
                    dp[i][j] = max(dp[i][j], dp[k - 1][j - 1] + range_max);
                }
            }
        }
        ret = max(ret, dp[i][m]);
    }

    for i in 1..n + 1 {
        for j in 1..m + 1 {
            print!("{} ", dp[i][j]);
        }
        println!("");
    }

    println!("{}", ret);
}