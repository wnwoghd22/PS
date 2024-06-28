use std::io;

fn pow(mut a: u64, mut k: u64, m: u64) -> u64 {
    let mut x = 1;
    while k > 0 {
        if k & 1 == 1 { x = x * a % m; }
        a = a * a % m;
        k >>= 1;
    }
    x
}

fn f(r: u64, n: u64, m: u64) -> u64 {
    if n == 1 { return 1; }
    let mut x = f(r, n / 2, m) * (pow(r, n / 2, m) + 1) % m;
    if n & 1 == 1 { x = (x + pow(r, n - 1, m)) % m; }
    x
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<u64> = s.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    println!("{}", v[0] * f(v[1], v[2], v[3]) % v[3]);
}