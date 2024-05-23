use std::io;

fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n1: Vec<u64> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let mut t = String::new();
    io::stdin().read_line(&mut t).unwrap();
    let n2: Vec<u64> = t
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let (num, den) = (n1[0] * n2[1] + n2[0] * n1[1], n1[1] * n2[1]);
    let g = gcd(num, den);
    let (num, den) = (num / g, den / g);
    println!("{} {}", num, den);
}