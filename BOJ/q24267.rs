use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: i64 = s.trim().parse().unwrap();
    let ret = n * (n - 1) / 2 * (n - 2) / 3;
    println!("{}\n{}", ret, 3);
}