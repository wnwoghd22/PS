use std::io::{self, BufRead};
use std::collections::VecDeque;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (_n, q, k) = (v[0], v[1], v[2]);

    let mut cmd: Vec<i32> = Vec::with_capacity(q);
    for _ in 0..q {
        let v: Vec<i32> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        cmd.push(if v[0] == 0 { v[1] } else { -v[0] });
    }
    println!("{:?}", cmd);

    let mut idx = 0;
    for i in (0..q).rev() {
        if cmd[i] == -1 {
            idx = i;
            break;
        }
    }
    let mut arr = vec![];
    for i in 0..idx {
        if cmd[i] > 0 {
            arr.push(cmd[i]);
        }
    }
    arr.sort();
    println!("{:?}", arr);

    let mut ret = VecDeque::from(arr);
    let mut is_front = true;
    for i in idx+1..q {
        if cmd[i] == -1 { panic!(); }
        if cmd[i] == -2 {
            is_front = !is_front;
        } else {
            if is_front { ret.push_front(cmd[i]); }
            else { ret.push_back(cmd[i]); }
        }
    }
    for _ in 1..k {
        if is_front { ret.pop_front(); }
        else { ret.pop_back(); }
    }
    println!("{}", if is_front { ret.front().unwrap() } else { ret.back().unwrap() });
}