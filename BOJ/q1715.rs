use std::io;
use std::collections::BinaryHeap;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u32 = s.trim().parse().unwrap();

    let mut pq: BinaryHeap<i64> = BinaryHeap::new();
    let mut ret = 0;
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let a: i64 = s.trim().parse().unwrap();
        pq.push(-a);
    }
    while let Some(x) = pq.pop() {
        if let Some(y) = pq.pop() {
            let z = x + y;
            ret -= z;
            pq.push(z);
        }
        else { break; }
    }
    println!("{}", ret);
}
