use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut sum = 0;
    let mut max = 0;
    for k in v {
        sum += k;
        if k > max { max = k; }
    }
    if sum - max <= max {
        sum = (sum - max) * 2 - 1;
    }
    println!("{}", sum);
}