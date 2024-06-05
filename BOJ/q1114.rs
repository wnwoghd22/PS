use std::io;

fn f(m: i32, l: i32, c: i32, p: &Vec<i32>) -> Option<i32> {
    let mut cnt = 0;
    let mut cur = l;

    for i in (1..p.len()).rev() {
        if cur - p[i] > m { return None; }
        if cur - p[i - 1] > m {
            cnt += 1;
            cur = p[i];
        }
    }

    if cnt > c { return None; }
    if cnt < c { cur = p[1]; }
    if cur > m { return None; }
    Some(cur)
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i32> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [len, _k, c] = v[..] else { panic!(); };
    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let mut p: Vec<i32> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    p.insert(0, 0);
    p.sort();

    let mut l = 1;
    let mut r = len;
    let mut ret = len;
    let mut pos = -1;
    while l <= r {
        let m = l + r >> 1;
        if let Some(x) = f(m, len, c, &p) {
            if m < ret {
                ret = m;
                pos = x;
            }
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    println!("{} {}", ret, pos);
}