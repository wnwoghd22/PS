use std::io::{self, BufRead};

fn get(c: char) -> usize {
    match c {
        'A' => 0,
        'C' => 1,
        'G' => 2,
        'T' => 3,
        _ => panic!(),
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (s, p) = (v[0], v[1]);

    let dna: Vec<char> = iter.next().unwrap().unwrap().trim().chars().collect();
    let cnt: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut cur: Vec<i32> = vec![0; 4];
    for &c in &dna[0..p-1] {
        cur[get(c)] += 1;
    }

    let mut ret = 0;
    for i in p-1..s {
        cur[get(dna[i])] += 1;
        let mut x = 1;
        for k in 0..4 {
            if cur[k] < cnt[k] {
                x = 0;
            }
        }
        ret += x;
        cur[get(dna[i + 1 - p])] -= 1;
    }
    println!("{}", ret);
}