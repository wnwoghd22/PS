use std::io::{self, BufRead, Write};
use std::collections::{BinaryHeap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    while let Some(line) = iter.next() {
        let line = line.unwrap();
        let mut stack: Vec<usize> = vec![];
        let mut sum: Vec<usize> = vec![0; 51];
        let mut cnt: Vec<usize> = vec![0; 51];
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
                    sum[cur] += stack[stack.len() - 1];
                    cnt[cur] += 1;
                    sum[stack[stack.len() - 1]] += cur;
                    cnt[stack[stack.len() - 1]] += 1;
                }
                cur = stack[stack.len() - 1];
                stack.pop();
            }
        }
        // println!("{:?}", cnt);
        // println!("{:?}", sum);

        for  i in 1..=50 {
            if cnt[i] == 1 {
                pq.push(50 - i);
            }
        }
        let mut f = false;
        while let Some(x) = pq.pop() {
            let x = 50 - x; // minimal leaf
            if cnt[x] != 1 { continue; }
            let adj = sum[x];
            // print!("node {} ", x);
            if f {
                _ = write!(writer, " "); 
            } else {
                f = true;
            }
            _ = write!(writer, "{}", adj);
            sum[adj] -= x;
            cnt[adj] -= 1;
            if cnt[adj] == 1 {
                pq.push(50 - adj);
            }
        }
        _ = write!(writer, "\n");
    }
    writer.flush().unwrap();
}