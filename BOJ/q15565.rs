use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, k] = v[..] else { panic!(); };

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let a: Vec<u8> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut r: usize = 0;
    let mut cnt = 0;
    let mut ret = n + 1;
    for l in 0..n {
        while r < n && cnt < k {
            if a[r] == 1 {
                cnt += 1;
            }
            r += 1;
            if cnt == k { break; }
        }

        if cnt == k && r - l < ret {
            ret = r - l;
        }
        
        if a[l] == 1 {
            cnt -= 1;
        }
    }
    if ret == n + 1 {
        println!("-1");
    } else {
        println!("{}", ret);
    }
}