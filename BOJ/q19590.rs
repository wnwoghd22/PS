use std::io::{self, BufRead};
use std::cmp::min;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut pairs = 0u64;
    let mut remains = 0u64;
    for _ in 0..n {
        let mut x: u64 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        if x <= remains {
            pairs += x;
            remains -= x;
        } else {
            let new_pairs = remains;
            x -= remains;
            let alter_pairs = min(pairs, x / 2);
            remains = x - alter_pairs * 2;
            pairs += new_pairs + alter_pairs;
        }
    }
    println!("{}", remains);
}

