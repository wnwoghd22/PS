use std::{io, collections::HashSet};

fn main() {
    let mut history = HashSet::new();
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u32 = s.trim().parse().unwrap();
    let mut cnt = 0;
    for _ in 0..n {
        let mut x = String::new();
        io::stdin().read_line(&mut x).unwrap();
        if x.trim() == "ENTER" {
            history.clear();
        } else {
            if !history.contains(&x) {
                cnt += 1;
                history.insert(x);
            }
        }
    }
    println!("{}", cnt);
}