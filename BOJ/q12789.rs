use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    
    let _n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut s: Vec<i32> = vec![];
    let a: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    
    let mut ret = true;
    let mut cur = 1;
    for i in a {
        while s.len() > 0 && s[s.len() - 1] == cur {
            cur += 1;
            s.pop();
        }
        if i == cur {
            cur += 1;
        } else {
            if s.len() == 0 || i < s[s.len() - 1] {
                s.push(i);
            } else {
                ret = false;
                break;
            }
        }
    }
    println!("{}", if ret { "Nice" } else { "Sad" });
}