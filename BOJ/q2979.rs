use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let cost: Vec<u32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut cnt: Vec<i32> = vec![0; 102];
    for _ in 0..3 {
        let time: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        cnt[time[0]] += 1;
        cnt[time[1]] -= 1;
    }
    let mut w: Vec<u32> = vec![0; 4];
    for i in 1..102 { cnt[i] += cnt[i - 1]; w[cnt[i] as usize] += 1; }
    println!("{:?}", cnt);
    println!("{:?}", w);
    
    let mut total = 0;
    for i in 1..4 {
        total += cost[i - 1] * w[i] * i as u32;
    }
    println!("{}", total);
}