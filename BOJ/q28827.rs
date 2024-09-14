use std::io::{self, BufRead};
use std::cmp::{min, max};

fn g(i: i128, k: i128, a: &Vec<i128>, s: &Vec<i128>) -> i128 {
    let mut cost = a[i as usize] - k;

    if i > 0 { // left
        let mut l = 0;
        let mut r = i - 1;
        let mut x = i;
        while l <= r {
            let m = l + r >> 1;
            if a[m as usize] > k + i - m {
                x = min(x, m);
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        if x < i {
            let cur = s[i as usize] - s[x as usize] - (i - x) * k;
            let slope = (i - x + 1) * (i - x) / 2;
            cost += cur - slope;
        }
    }

    if (i as usize) < a.len() - 1 { // right
        let mut l = i + 1;
        let mut r = a.len() as i128 - 1;
        let mut x = i;
        while l <= r {
            let m = l + r >> 1;
            if a[m as usize] > k + m - i {
                x = max(x, m);
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        
        if x > i {
            let cur = s[(x + 1) as usize] - s[(i + 1) as usize] - (x - i) * k;
            let slope = (x - i + 1) * (x - i) / 2;
            cost += cur - slope;
        }
    }

    cost
}

fn f(i: usize, a: &Vec<i128>, s: &Vec<i128>, t: i128) -> i128 {
    let mut l: i128 = -1e18 as i128;
    let mut ret = a[i];
    let mut r = ret;
    while l <= r {
        let m = l + r >> 1;
        if g(i as i128, m, a, s) <= t {
            ret = min(ret, m);
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    ret
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<i128> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n: usize = v[0] as usize;
    let t = v[1];

    let a: Vec<i128> = iter.next().unwrap().unwrap()
    .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut s: Vec<i128> = vec![0; n + 1];
    for i in 0..n {
        s[i + 1] = s[i] + a[i];
    }
    let mut ret = 1e18 as i128;
    for i in 0..n {
        ret = min(ret, f(i, &a, &s, t));
    }
    println!("{}", ret);
}