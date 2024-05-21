use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();
    
    let s = iterator.next().unwrap().unwrap();
    let n: usize = s.trim().parse().unwrap();

    let mut stack = vec![];
    let mut ret: u64 = 0;
    for _ in 0..n {  
        let s = iterator.next().unwrap().unwrap();
        let h: u64 = s.trim().parse().unwrap();
        while stack.len() > 0 {
            if stack[stack.len() - 1] <= h {
                stack.pop();
            }
            else { break; }
        }
        ret += stack.len() as u64;
        stack.push(h);
    }
    println!("{}", ret);
}