use std::io;
use std::collections::BinaryHeap;

fn main() {
    let mut sum: i64 = 0;

    let mut positive_queue: BinaryHeap<i64> = BinaryHeap::new();
    let mut negative_queue: BinaryHeap<i64> = BinaryHeap::new();

    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let n: i32 = s.trim().parse().expect("not a number");

    for _ in 0..n {
        let mut x = String::new();
        io::stdin().read_line(&mut x).expect("no input");
        let a: i64 = x.trim().parse().expect("not a number");
        if a < 1 { negative_queue.push(-a); }
        else if a == 1 { sum += 1; }
        else if a > 1 { positive_queue.push(a); }
    }

    while let Some(k) = positive_queue.pop() {
        if let Some(l) = positive_queue.pop() {
            sum += k * l;
        }
        else {
            sum += k;
        }
    }
    while let Some(k) = negative_queue.pop() {
        if let Some(l) = negative_queue.pop() {
            sum += k * l;
        }
        else {
            sum -= k;
        }
    }

    println!("{}", sum);
}