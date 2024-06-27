use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let [n, m] = v[..] else { panic!(); };
    let mut sum: Vec<u64> = vec![0; m + 1];
    for _ in 0..n {
        let v: Vec<u64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        for i in 0..m { sum[i + 1] += v[i]; }
    }
    let a: usize = iter.next().unwrap().unwrap().parse().unwrap();
    for i in 1..a { sum[i] += sum[i - 1]; }
    let mut ret = 0;
    for i in a..m+1 {
        sum[i] += sum[i - 1];
        ret = max(ret, sum[i] - sum[i - a]);
    }
    println!("{}", ret);
}