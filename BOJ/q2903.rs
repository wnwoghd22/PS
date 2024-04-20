use std::io;

fn main() {
    let a: u64 = 2;
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let x: u32 = s.trim().parse().expect("not a number");

    let b = a + (1 << x) - 1;
    println!("{}", b * b);
}