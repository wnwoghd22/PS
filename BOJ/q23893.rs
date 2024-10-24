use std::io::{self, BufRead};
use std::collections::HashMap;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (_n, p, k) = (v[0], v[1], v[2]);

    let arr: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut map: HashMap<i64, i64> = HashMap::new();
    for a in arr {
        let key = (a * a % p * a - k * a % p + p) % p;
        *map.entry(key).or_insert(0) += 1;
    }
    let mut ret = 0;
    for (_, v) in map.iter() {
        ret += v * (v - 1) / 2;
    }
    println!("{}", ret);
}