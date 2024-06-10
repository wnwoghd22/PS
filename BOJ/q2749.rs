use std::io;

static MOD: u64 = 1_000_000;

fn mul(l: &Vec<u64>, r: &Vec<u64>) -> Vec<u64> {
    vec![
        (l[0] * r[0] + l[1] * r[2]) % MOD,
        (l[0] * r[1] + l[1] * r[3]) % MOD,
        (l[2] * r[0] + l[3] * r[2]) % MOD,
        (l[2] * r[1] + l[3] * r[3]) % MOD,
    ]
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let mut n: u64 = s.trim().parse().unwrap();
    
    let mut ret = vec![1, 0, 0, 1];
    let mut v = vec![1, 1, 1, 0];
    while n > 0 {
        if n & 1 == 1 { ret = mul(&ret, &v); }
        v = mul(&v, &v);
        n >>= 1;
    }
    println!("{:?}", ret);
}