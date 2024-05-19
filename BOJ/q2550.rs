use std::io::{self, BufRead};
use std::cmp::min;

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();

    let s = iterator.next().unwrap().unwrap();
    let n: usize = s.trim().parse().unwrap();

    let s = iterator.next().unwrap().unwrap();
    let source: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let s = iterator.next().unwrap().unwrap();
    let target: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut pos: Vec<usize> = vec![0; n + 1];
    for i in 0..n { pos[target[i]] = i + 1; }

    let mut dp: Vec<usize> = vec![0; n];
    let mut lis: Vec<usize> = vec![0];

    for i in 0..n {
        let k = pos[source[i]];
        if k > lis[lis.len() - 1] {
            dp[i] = lis.len();
            lis.push(k);
        }
        else {
            let mut l = 1;
            let mut r = lis.len() - 1;
            let mut x = lis.len() - 1;
            while l <= r {
                let m = l + r >> 1;
                if lis[m] >= k {
                    x = min(x, m);
                    r = m - 1;
                }
                else { l = m + 1; }
            }
            dp[i] = x;
            lis[x] = k;
        }
    }

    let len = lis.len() - 1;
    let mut ret = vec![];
    let mut cur = len;
    for i in (0..n).rev() {
        if dp[i] == cur {
            if ret.is_empty() || pos[source[i]] < pos[ret[ret.len() - 1]] {
                ret.push(source[i]);
                cur -= 1;
            }
        }
    }
    ret.sort();
    println!("{}", len);
    for e in ret {
        print!("{} ", e);
    }
}