use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    
    let mut arr: Vec<(i64, i64)> = vec![];
    for _ in 0..n {
        let v: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        arr.push((v[0], v[1]));
    }
    arr.sort();
    let mut ret = 0;
    let mut _l = 0;
    let mut r = 0;
    let mut m = 0;
    for (_x, d) in arr {
        if d == -1 { // left
            ret += r;
            ret += 2 * m;
            _l += 1;
        }
        if d == 1 { // right
            ret -= 2 * m;
            r += 1;
        }
        if d == 0 {
            m += 1;
        }
    }
    ret += r * m * 2;
    println!("{}", ret);
}