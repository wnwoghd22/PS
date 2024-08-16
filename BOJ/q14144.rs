use std::io::{self, BufRead};
use std::cmp::min;

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { 
        return a;
    } else {
        gcd(b, a % b)
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut pos: Vec<i64> = vec![0; n + 1];
    for k in 1..=n {
        let x: i64 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut l = 1;
        let mut r = 1e18 as i64;
        pos[k] = r;
        while l <= r {
            let m = l + r >> 1;
            let mut cnt = m / k as i64;
            for bit in 1..1<<k-1 {
                let mut p = m;
                let mut mu = 1;
                let mut lcm = k as i64;
                for b in 0..k-1 {
                    if bit & 1 << b == 0 { continue; }
                    p = min(p, pos[b + 1]);
                    lcm = lcm * (b + 1) as i64 / gcd(lcm, (b + 1) as i64);
                    mu *= -1;
                }
                cnt += mu * p / lcm;
            }
            if cnt >= x {
                pos[k] = min(pos[k], m);
                r = m - 1;
            }
            else { l = m + 1; }
        }
    }
    for i in 1..=n { println!("{}", pos[i]); }
}