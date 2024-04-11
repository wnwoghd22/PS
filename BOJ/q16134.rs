use std::io;

const MOD: u64 = (1e9 + 7.0) as u64;

fn pow(mut a: u64, mut b: u64) -> u64 {
    let mut ret: u64 = 1;
    while b > 0 {
        if b & 1 == 1 {ret = ret * a % MOD; }
        a = a * a % MOD;
        b >>= 1;
    }
    ret
}

fn main() {
    let mut s = String::new();
    let mut facto = vec![0; 1000001];
    facto[0] = 1;
    for i in 1..1000001 {
        facto[i] = facto[i - 1] * (i as u64) % MOD;
    }

    io::stdin().read_line(&mut s).unwrap();

    let values:Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let num = facto[values[0]];
    let den = pow(facto[values[1]], MOD - 2) * 
        pow(facto[values[0] - values[1]], MOD - 2) % MOD;

    println!("{}", num * den % MOD);
}