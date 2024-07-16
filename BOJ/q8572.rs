use std::io::{self, BufRead, Write};
use std::collections::BinaryHeap;
use std::mem;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    
    let mut a: Vec<char> = iter.next().unwrap().unwrap().chars().collect();
    let mut b: Vec<char> = iter.next().unwrap().unwrap().chars().collect();
    
    let mut pqa: BinaryHeap<usize> = BinaryHeap::new();
    let mut pqb: BinaryHeap<usize> = BinaryHeap::new();
    for i in 0..n {
        if a[i] < b[i] { pqa.push(n - i); }
        if b[i] < a[i] { pqb.push(n - i); }
    }

    let t: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let i = v[0];
        let j = v[1];
        mem::swap(&mut a[i], &mut b[j]);
        if a[i] < b[i] { pqa.push(n - i); }
        if b[i] < a[i] { pqb.push(n - i); }
        if a[j] < b[j] { pqa.push(n - j); }
        if b[j] < a[j] { pqb.push(n - j); }
        while let Some(x) = pqa.peek() {
            let k = n - x;
            if a[k] >= b[k] { pqa.pop(); }
            else { break; }
        }
        while let Some(x) = pqb.peek() {
            let k = n - x;
            if b[k] >= a[k] { pqb.pop(); }
            else { break; }
        }
        let l = pqa.peek().unwrap_or(&0);
        let r = pqb.peek().unwrap_or(&0);
        _ = writeln!(writer, "{}", if l == r {
            0
        } else if l < r {
            1
        } else {
            2
        });
    }
    writer.flush().unwrap();
}