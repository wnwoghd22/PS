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
    let [M, N, L] = values[..] else { panic!(); };
    let L = L as i64;

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let mut pos: Vec<i64> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    pos.sort();

    let mut ret = 0;
    for _ in 0..N {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let values: Vec<i64> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [a, b] = values[..] else { panic!(); };
        let mut l: i64 = 0;
        let mut r: i64 = (M - 1) as i64;
        let mut i = 0;
        while l <= r {
            let m = (l + r >> 1) as usize;
            if pos[m] <= a {
                i = max(i, m);
                l = m as i64 + 1;
            }
            else { r = m as i64 - 1; }
        }
        if pos[i] <= a {
            if a - pos[i] + b <= L || i + 1 < M && pos[i + 1] - a + b <= L {
                ret += 1;
            }
        }
        else if pos[i] - a + b <= L {
            ret += 1;
        }
    }
    println!("{}", ret);
}