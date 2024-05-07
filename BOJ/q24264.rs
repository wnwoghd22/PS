use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u64 = s. trim().parse().unwrap();
    println!("{}\n{}", n * n, 2);
}