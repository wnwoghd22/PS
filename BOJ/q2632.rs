use std::io::{self, BufRead};
use std::collections::HashMap;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut map: HashMap<u32, u64> = HashMap::new();
    let w: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut a: Vec<u32> = vec![0; v[0]];
    let mut b: Vec<u32> = vec![0; v[1]];
    for i in 0..v[0] {
        let w: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        a[i] = w;
    }
    for i in 0..v[1] {
        let w: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        b[i] = w;
    }
    map.insert(0, 1);
    map.insert(a.iter().sum(), 1);
    for i in 0..v[0] {
        let mut s = a[i];
        let mut j = i;
        *map.entry(s).or_insert(0) += 1;
        loop {
            j = (j + 1) % v[0];
            if j == (i + v[0] - 1) % v[0] {
                break;
            }
            s += a[j];
            *map.entry(s).or_insert(0) += 1;
        }
    }

    let mut ret: u64 = 0;
    if map.contains_key(&w) {
        ret += map[&w]; 
    }
    let bs: u32 = b.iter().sum();
    if bs <= w && map.contains_key(&(w - bs)) {
        ret += map[&(w - bs)];
    }
    for i in 0..v[1] {
        let mut s = b[i];
        let mut j = i;
        if s > w { continue; }
        if map.contains_key(&(w - s)) {
            ret += map[&(w - s)];
        }
        loop {
            j = (j + 1) % v[1];
            if j == (i + v[1] - 1) % v[1] {
                break;
            }
            s += b[j];
            if s > w { break; }
            if map.contains_key(&(w - s)) {
                ret += map[&(w - s)];
            }
        }
    }

    println!("{}", ret);
}