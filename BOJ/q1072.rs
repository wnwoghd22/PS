use std::io;
use std::cmp::min;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i64> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [x, y] = v[..] else { panic!(); };
    if y * 100 / x >= 99 { println!("-1"); return; }

    let z = y * 100 / x;
    let mut l = 0;
    let mut r = x;
    let mut ans = x;
    while l <= r {
        let m = l + r >> 1;
        let k = (y + m) * 100 / (x + m);
        if k > z {
            ans = min(ans, m);
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    println!("{}", ans);
}