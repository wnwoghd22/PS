use std::io;
use std::cmp::max;

const INF: i64 = 1e12 as i64;

fn f(n: i64, m: i64, k: i64, x: i64) -> bool {
    let mut s = 0;
    let mut g = 0;
    while s < k && g < n {
        let y = (n - g) / x;
        if y < m {
            g += m * (k - s);
            break;
        }
        let mut d = (n - x * y - g) / y + 1;
        if d > k - s { d = k - s; }
        g += y * d;
        s += d;
    }
    g >= n
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, k, m) = (v[0], v[1], v[2]);
    let mut l = 1;
    let mut r = INF;
    let mut x = 1;
    while l <= r {
        let mid = l + r >> 1;
        if f(n, m, k, mid) {
            x = max(x, mid);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    println!("{}", x);
}