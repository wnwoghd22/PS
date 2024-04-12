use std::io;

fn f(n: u64) -> u64 {
    if n == 0 {
        1
    }
    else {
        n * f(n - 1)
    }
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let n: u64 = s.trim().parse().expect("number");

    println!("{}", f(n));
}