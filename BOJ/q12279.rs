use std::io::{self, BufRead};

enum Output {
    Fraction((u64, u64)),
    Position(u64),
}

impl std::fmt::Display for Output {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Output::Fraction((p, q)) => write!(f, "{} {}", p, q),
            Output::Position(k) => write!(f, "{}", k), 
        }
    }
}

fn query1(n: u64) -> Output {
    let mut p = 1u64;
    let mut q = 1u64;
    let mut k = 0;
    for i in 0..64 {
        if n & 1 << i != 0 { 
            k = 1 << i;
        }
    }

    k >>= 1;
    while k > 0 {
        if n & k == 0 {
            q = p + q;
        } else {
            p = p + q;
        }
        k >>= 1;
    }

    Output::Fraction((p, q))
}
fn query2(mut p: u64, mut q: u64) -> Output {
    let mut ret = 0;
    let mut k = 1;

    while p > 0 && q > 0 {
        if p >= q {
            p = p - q;
            ret |= k;
        } else {
            q = q - p;
        }
        k <<= 1;
    }
    Output::Position(ret)
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let t: u32 = iter.next().unwrap().unwrap().parse().unwrap();
    for tc in 1..t+1 {
        let v: Vec<u64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let ret: Output = if v[0] == 1 {
            query1(v[1])
        } else {
            query2(v[1], v[2])
        };
        println!("Case #{}: {}", tc, ret);
    }
}