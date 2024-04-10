use std::io;
const MOD: i64 = 1e12 as i64;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");

    let mut x: i64 = 1;
    let n: i64 = s.trim().parse().expect("number");

    for i in 1..n + 1 {
        x = x * i;
        while x % 10 == 0 {
            x /= 10;
        }
        x %= MOD;
    }

    println!("{:05}", x % 100000);
}