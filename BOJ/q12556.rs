use std::io::{self, BufRead};
use std::collections::HashSet;

const LEN: usize = 1_000_001;
const AMBIGUOUS: &str = "I don't know.";

fn pow(mut n: i64, mut k: i64, p: i64) -> i64 {
    let mut x = 1;
    while k > 0 {
        if k & 1 == 1 { x = x * n % p; }
        n = n * n % p;
        k >>= 1;
    }
    x
}

fn main() {
    let mut sieve = [false; LEN];
    for i in 2..LEN {
        if sieve[i] { continue; }
        for j in (i*2..LEN).step_by(i) {
            sieve[j] = true;
        }
    }

    let mut iter = io::stdin().lock().lines();
    let tc: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    
    'testcase:
    for t in 1..=tc {
        print!("Case #{}: ", t);
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let (d, k) = (v[0], v[1]);
        let x: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();

        if k == 1 {
            println!("{}", AMBIGUOUS);
            continue 'testcase;
        }
        if k == 2 {
            if x[0] == x[1] {
                println!("{}", x[0]);
            } else {
                println!("{}", AMBIGUOUS);
            }
            continue 'testcase;
        }

        if x[0] == x[1] {
            println!("{}", x[0]);
            continue 'testcase;
        }

        let mut ret: HashSet<i64> = HashSet::new();
        let mut pv = 2;
        for &a in &x {
            if a + 1 > pv {
                pv = a + 1;
            }
        }
        'primes:
        for p in pv..pow(10, d as i64, LEN as i64) {
            if sieve[p as usize] { continue; }
            let a = (x[2] - x[1] + p) % p * pow((x[1] - x[0] + p) % p, p - 2, p) % p;
            let b = (x[1] - a * x[0] % p + p) % p;
            for j in 3..x.len() {
                if (a * x[j - 1] + b) % p != x[j] {
                    continue 'primes;
                }
            }
            ret.insert((a * x[x.len() - 1] + b) % p); 
        }
        if ret.len() > 1 {
            println!("{}", AMBIGUOUS);
        } else {
            for e in ret {
                println!("{}", e);
            }
        }
    }
}