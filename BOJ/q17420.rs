use std::io;
use std::cmp::max;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: usize = s.trim().parse().unwrap();

    let mut s1 = String::new();
    io::stdin().read_line(&mut s1).unwrap();
    let a: Vec<i64> = s1.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    
    let mut s2 = String::new();
    io::stdin().read_line(&mut s2).unwrap();
    let b: Vec<i64> = s2.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    
    let mut arr: Vec<(i64, i64)> = vec![(0, 0); n];
    for i in 0..n {
        arr[i] = (b[i], a[i]);
    }
    arr.sort();
    let mut ret = 0i64;
    let mut pre_max = -1;
    let mut cur_max = -1;
    for i in 0..n {
        let (b, a) = arr[i];
        let mut cur = a;
        if b > pre_max { pre_max = b; }
        if pre_max > a {
            let cnt = (pre_max - a + 29) / 30;
            ret += cnt;
            cur += cnt * 30;
        }
        cur_max = max(cur_max, cur);
        if i < n - 1 && b != arr[i + 1].0 {
            pre_max = cur_max;
        }
    }
    println!("{}", ret);
}