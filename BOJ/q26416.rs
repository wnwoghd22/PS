use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let t: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for tc in 0..t {
        let _n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut s: Vec<char> = iter.next().unwrap().unwrap().trim().chars().collect();
        let mut num = false;
        let mut upper = false;
        let mut lower = false;
        let mut special = false;
        for c in &s {
            if c.is_ascii_uppercase() { upper = true; }
            if c.is_ascii_lowercase() { lower = true; }
            if c.is_numeric() { num = true; }
            if *c == '#' || *c == '@' || *c == '*' || *c == '&' { special = true; }
        }
        if !num { s.push('1'); }
        if !upper { s.push('A'); }
        if !lower { s.push('a'); }
        if !special { s.push('*'); }
        while s.len() < 7 {
            s.push('1');
        }
        println!("Case #{}: {}", tc + 1, s.iter().collect::<String>());
    }
}