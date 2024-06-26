use std::io::{self, BufRead};

fn main() {
    let lines = io::stdin().lock().lines();
    let mut f: Vec<u32> = vec![1];
    for k in 1..10 { f.push(f[f.len() - 1] * k); }

    for line in lines {
        let s = line.unwrap();
        let v: Vec<&str> = s.split_whitespace().collect();
        let mut c: Vec<char> = v[0].chars().collect();
        c.sort();
        let mut ret: Vec<char> = vec![];
        let len = c.len();
        let mut k: u32 = v[1].parse().unwrap();
        let mut b: Vec<bool> = vec![false; len];
        for i in 1..len+1 {
            let mut p = 0;
            for j in 0..len {
                if b[j] { continue; }
                p += 1;
                if f[len - i] * p >= k {
                    ret.push(c[j]);
                    b[j] = true;
                    k -= f[len - i] * (p - 1);
                    break;
                }
            }
        }
        let ans = if ret.len() > 0 {
            ret.iter().collect::<String>()
        } else {
            "No permutation".to_string()
        };
        println!("{} = {}", s, ans);
    }
}