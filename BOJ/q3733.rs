use std::io::{self, BufRead};

fn main() {
    let iter = io::stdin().lock().lines();
    for s in iter {
        let v: Vec<i32> = s.unwrap().split_whitespace().map(|x| x.parse().unwrap()).collect();
        println!("{}", v[1] / (v[0] + 1));
    }
}