use std::io::{self, BufRead};
use std::cmp::min;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut a = vec![0; v[0]];
    let mut b = vec![0; v[1]];
    for i in 0..v[0] {
        let h: u64 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        a[i] = h;
    }
    for j in 0..v[1] {
        let h: u64 = iter.next().unwrap().unwrap().trim().parse().unwrap();
        b[j] = h;
    }
    a.sort();
    b.sort();
    let mut cnt = 0u64;
    let mut i = a.len() - 1;
    let mut j = b.len() - 1;
    let mut ii = true;
    let mut jj = true;
    if a[i] != b[j] {
        println!("-1");
        return;
    }
    while ii && jj {
        if a[i] == b[j] {
            cnt += a[i];
            if i == 0 { ii = false; }
            else { i -= 1; }
            if j == 0 { jj = false; }
            else { j -= 1; }
        }
        else if a[i] > b[j] {
            while ii && a[i] > b[j] {
                cnt += a[i];
                if i == 0 { ii = false; }
                else { i -= 1; }
            }
        }
        else {
            while jj && b[j] > a[i] {
                cnt += b[j];
                if j == 0 { jj = false; }
                else { j -= 1; }
            }
        }
    }
    while ii { 
        cnt += a[i];
        if i == 0 { ii = false; }
        else { i -= 1; }
    }
    while jj {
        cnt += b[j];
        if j == 0 { jj = false; }
        else { j -= 1; }
    }

    print!("{} ", cnt);

    cnt = 0;
    let mut cur = 0;
    i = 0;
    j = 0;
    while i < a.len() && j < b.len() {
        let x = min(a[i], b[j]);
        cnt += (x - cur) * (a.len() - i) as u64 * (b.len() - j) as u64;
        cur = x;
        while i < a.len() && a[i] == cur { i += 1; }
        while j < b.len() && b[j] == cur { j += 1; }
    }

    println!("{}", cnt);
}