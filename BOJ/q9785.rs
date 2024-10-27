use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();

    let a: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, m) = (a[0], a[1]);
    let mut arr: Vec<(i32, i32)> = vec![];
    for _ in 0..n {
        let a: Vec<i32> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        arr.push((a[0], a[1]));
    }
    arr.sort();
    let mut sum = 0;
    let mut time = 1_000_000_000;
    for i in 0..m {
        let j = n - i - 1;
        sum += arr[j].0;
        if arr[j].1 < time {
            time = arr[j].1;
        }
    }
    println!("{} {}", sum, time);
}