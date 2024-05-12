use std::io;
use std::cmp::max;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, d, k, c] = values[..] else {panic!();};
    let mut cnts = vec![0; d + 1];
    let mut cnt = 1;
    cnts[c] += 1;

    let mut arr: Vec<usize> = vec![0; n + k];
    for i in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        arr[i] = s.trim().parse().unwrap();
    }
    for i in 0..k {
        if cnts[arr[i]] == 0 { cnt += 1; }
        cnts[arr[i]] += 1;
        arr[i + n] = arr[i];
    }
    let mut ret = cnt;
    for i in 0..n-1 {
        if cnts[arr[i + k]] == 0 { cnt += 1; }
        cnts[arr[i + k]] += 1;
        cnts[arr[i]] -= 1;
        if cnts[arr[i]] == 0 { cnt -= 1; }
        ret = max(ret, cnt);
    }
    println!("{}", ret);
}