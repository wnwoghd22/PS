use std::io::{self, BufRead};
use std::collections::{BinaryHeap};
use std::cmp::min;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let a: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let s: i64 = a.iter().sum();

    println!("{}", s);

    let mut cur = 0;
    let mut r = 0;
    let mut pq: BinaryHeap<(i64, usize)> = BinaryHeap::new();
    let mut ret = n + 1;
    for l in 0..n {
        while let Some((_x, i)) = pq.peek() {
            if *i < l { pq.pop(); }
            else { break; }
        }
        while r < n && cur * 2 < s {
            cur += a[r];
            pq.push((-a[r], r));
            r += 1;
        }
        if let Some((x, _i)) = pq.peek() {
            println!("{} {} {} {}", l, r, cur, -x);
            if (cur + *x) * 2 >= s {
                println!("ans: {} {} {} {}", l, r, cur, -x);
                ret = min(ret, r - l - 1);
            } else if cur * 2 >= s {
                println!("ans: {} {} {} {}", l, r, cur, -x);
                ret = min(ret, r - l);
            }
        }
        cur -= a[l];
    }
    println!("{}", ret);
}