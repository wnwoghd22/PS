use std::io::{self, BufRead, Write};

const LEN: usize = 10001;

fn main() {
    let mut p = [false; 500];
    for i in 2..500 {
        if p[i] {  continue; }  
        for j in (i..500).step_by(i) {
            p[j] = true;
        }
    }

    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let d: i32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..d {
        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        // 
    }
}