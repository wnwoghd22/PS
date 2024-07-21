use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<u64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = v[2] as usize;
    let mut parts: Vec<(u64, u64, usize)> = vec![];
    for i in 0..n {
        let v: Vec<u64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        parts.push((v[0], v[1], i));
    }
    parts.sort_by(|a: &(u64, u64, _), b: &(u64, u64, _)| {
        (a.1 * b.0).cmp(&(a.0 * b.1))
    });
    println!("{:?}", parts);

    let mut check: Vec<bool> = vec![false; n];
    let mut num = v[0];
    let mut den = v[1];
    let mut cnt = 0;
    for (f, m, i) in parts {
        if (num + f) * den >= num * (den + m) {
            num += f;
            den += m;
            check[i] = true;
            cnt += 1;
        }
    }
    if cnt == 0 {
        println!("NONE");
    } else {
        for i in 0..n {
            if check[i] {
                println!("{}", i + 1);
            }
        }
    }
}