use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<i32> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    println!("{}", if v[0] % 2 == 0 || v[1] % 2 == 0 || (v[2] + v[3]) % 2 != 0 {
        "Yes"
    } else {
        "Lose"
    });
}