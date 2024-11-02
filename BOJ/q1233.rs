use std::io;
fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let a: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut cnt = vec![0; 100];
    for i in 1..=a[0] {
        for j in 1..=a[1] {
            for k in 1..a[2] {
                cnt[i + j + k] += 1;
            }
        }
    }
    let mut ret = 0;
    for i in 1..100 {
        if cnt[i] > cnt[ret] {
            ret = i;
        }
    }
    println!("{}", ret);
}