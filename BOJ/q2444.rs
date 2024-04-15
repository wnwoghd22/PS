use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let n: i32 = s.trim().parse().expect("number");

    for i in 1..n {
        for j in 0..n-i { print!(" "); }
        for j in 1..i*2 { print!("*"); }
        println!("");
    }
    for i in 1..n*2 { print!("*"); }
    println!("");
    for i in (1..n).rev() {
        for j in 0..n-i { print!(" "); }
        for j in 1..i*2 { print!("*"); }
        println!("");
    }
}