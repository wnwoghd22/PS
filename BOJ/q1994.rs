use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut arr: Vec<i32> = vec![];
    for _ in 0..n {
        let x: i32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        arr.push(x);
    }
    arr.sort();
    let mut ret = 0;
    let mut a: Vec<i32> = vec![];
    let mut cur = -1;
    for x in arr {
        if x != cur {
            a.push(x);
            cur = 1;
        } else {
            cur += 1;
        }
        ret = max(ret, cur);
    }
    let mut dp: Vec<Vec<i32>> = vec![vec![0; n]; n];

    for i in 0..a.len() {
        let mut k = i;
        for j in (0..i).rev() {
            let d = a[i] - a[j];
            while k > 0 && a[j] - a[k - 1] <= d {
                k -= 1;
            }
            dp[i][j] = max(dp[i][j], if a[j] - a[k] == d {
                dp[j][k] + 1
            } else { 2 });
            ret = max(ret, dp[i][j]);
        }
    }
    println!("{}", ret);
}