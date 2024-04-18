use std::io;

fn main() {
    let mut s = String::new();

    while let Ok(n) = io::stdin().read_line(&mut s) {
        if n == 0 { break; }
        print!("{}", s);
        s.clear();
    }
}