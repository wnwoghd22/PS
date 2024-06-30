use std::io;

fn f(x: i32) -> i32 {
    let mut l = 0;
    let mut r = x;
    let mut k = 0;
    while l <= r {
        let m = l + r >> 1;
        if m * (m + 1) / 2 <= x {
            if m > k {
                k = m;
            }
            l = m + 1;
        } else { r = m - 1; }
    }
    x * (k + 1) - k * (k + 1) * (k + 2) / 6
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i32> = s.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    println!("{}", f(v[1]) - f(v[0] - 1));
}