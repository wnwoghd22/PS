use std::io::{self, BufRead, Write};
use std::collections::{BinaryHeap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    while let Some(line) = iter.next() {
        let line = line.unwrap();
        let mut stack: Vec<usize> = vec![];
        let mut g: Vec<Vec<usize>> = vec![vec![]; 51];
        let mut pq: BinaryHeap<usize> = BinaryHeap::new();
        let mut cur = 0;
        for c in line.as_bytes() {
            if *c >= b'0' && *c <= b'9' {
                cur = cur * 10 + (c - b'0') as usize;
            } else if *c == b'(' {
                stack.push(cur as usize);
                cur = 0;
            } else if *c == b')' {
                if stack[stack.len() - 1] != 0 {
                    g[cur].push(stack[stack.len() - 1]);
                    g[stack[stack.len() - 1]].push(cur);
                    cur = stack[stack.len() - 1];
                }
                stack.pop();
            }
        }
        for  i in 1..=50 {
            if g[i].len() == 1 {
                pq.push(50 - i);
            }
        }
        while let Some(x) = pq.pop() {
            let x = 50 - x; // minimal leaf
            // print!("{} ", x);
            
        }
        println!("");
    }
}