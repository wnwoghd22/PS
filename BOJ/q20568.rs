use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut a: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    a.sort();
    let mut cur = -1;
    let mut cnt = n;
    for i in a {
        if i != cur { cnt -= 1; }
        cur = i;
    }
    println!("{}", cnt);
}