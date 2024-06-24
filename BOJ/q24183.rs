use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i32> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let c4: f64 = (2 * 229 * 324) as f64 * v[0] as f64;
    let a3: f64 = (2 * 297 * 420) as f64 * v[1] as f64;
    let a4: f64 = (210 * 297) as f64 * v[2] as f64;

    println!("{:7}", (c4 + a3 + a4) * 0.000001);
}