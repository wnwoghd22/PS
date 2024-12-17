use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    
    let mut t = String::new();
    io::stdin().read_line(&mut t).unwrap();

    println!("{}", if s.len() >= t.len() {
        "go"
    } else {
        "no"
    });
}