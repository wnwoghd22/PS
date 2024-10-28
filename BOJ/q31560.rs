use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();

    let n: i64 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let arr: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut ret = 0i64;
    let mut a = 0;
    let mut b = 0;
    for i in 0..n {
        let dx = arr[i as usize] + a * (i + 1) + b;
        ret += dx.abs();
        b += i * dx;
        a -= dx;
    }
    println!("{}", ret);
}