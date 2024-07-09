use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<u64> = s.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    if v[1] >= v[0] {
        println!("{}", (v[0] - 1) * 2);
        if v[0] & 1 == 1 {
            println!("{} {}", v[0] / 2 + 1, v[1] - v[0] / 2);
        } else {
            println!("{} {}", v[0] - v[0] / 2 + 1, v[0] / 2);
        }
    } else {
        println!("{}", (v[1] - 1) * 2 + 1);
        if v[1] & 1 == 1 {
            println!("{} {}", v[0] - v[1] / 2, v[1] / 2 + 1);
        } else {
            println!("{} {}", v[1] / 2 + 1, v[1] / 2);
        }
    }
}