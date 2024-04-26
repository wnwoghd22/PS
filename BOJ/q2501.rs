use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<u32> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let (n, k) = (values[0], values[1]);

    let mut ret = 0;
    let mut cnt = 0;
    for p in 1..n + 1 {
        if n % p == 0 {
            cnt += 1;
            if cnt == k {
                ret = p;
                break;
            }
        }
    }
    println!("{}", ret);
}