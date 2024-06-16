use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    
    let s = iterator.next().unwrap().unwrap();
    let _n: usize = s.trim().parse().unwrap();

    let mut cnt: Vec<u32> = vec![0; 2001];

    let s = iterator.next().unwrap().unwrap();
    let a: Vec<i32> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    for e in a {
        let i = (e + 1000) as usize;
        cnt[i] += 1;
    }
    for i in 0..2001 {
        if cnt[i] > 0 {
            print!("{} ", i as i32 - 1000);
        }
    }
}