use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u32 = s.trim().parse().unwrap();
    let mut e: f64 = 1.;
    let mut x: f64 = 1.;
    for i in 1..n+1 {
        x /= i as f64;
        e += x;
    }
    println!("{}", e);
}