use std::io::{self, BufRead};
use std::cmp::max;

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    let n: usize = iterator.next().unwrap().unwrap().parse().unwrap();

    let s = iterator.next().unwrap().unwrap();
    let mut a1: Vec<i32> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let s = iterator.next().unwrap().unwrap();
    let a2: Vec<i32> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    
    let mut cnt = 0;
    for i in 0..n {
        if a1[i] == a2[i] { 
            cnt += 1; 
        }
    }
    let mut ret = cnt;
    for i in (1..n).rev() {
        for j in 0..i {
            if a1[j] > a1[j + 1] {
                if a1[j] == a2[j] { 
                    cnt -= 1; 
                }
                if a1[j + 1] == a2[j + 1] { 
                    cnt -= 1; 
                }

                let temp = a1[j];
                a1[j] = a1[j + 1];
                a1[j + 1] = temp;

                if a1[j] == a2[j] { 
                    cnt += 1; 
                }
                if a1[j + 1] == a2[j + 1] { 
                    cnt += 1; 
                }
            }
            ret = max(ret, cnt);
        }
    }
    println!("{}", if ret == n {
        1
    } else {
        0
    });
}