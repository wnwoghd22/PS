use std::io;
use std::collections::VecDeque;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let n: usize = s.trim().parse().expect("not a number");

    let mut a = String::new();
    io::stdin().read_line(&mut a).expect("no input");
    let is_stack: Vec<u32> = a
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut b = String::new();
    io::stdin().read_line(&mut b).expect("no input");
    let elem: Vec<u32> = b
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();


    let mut q: VecDeque<u32> = VecDeque::new();
    for i in 0..n {
        if is_stack[i] != 1 {
            q.push_front(elem[i]);
        }
    }

    let mut t = String::new();
    io::stdin().read_line(&mut t).expect("no input");
    let _m: usize = t.trim().parse().expect("not a number");

    let mut c = String::new();
    io::stdin().read_line(&mut c).expect("no input");
    let inputs: Vec<u32> = c
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    for e in inputs {
        q.push_back(e);
        if let Some(x) = q.pop_front() {
            print!("{} ", x);
        }
    }
}