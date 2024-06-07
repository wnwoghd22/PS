use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<_> = s
        .as_mut_str()
        .split_whitespace()
        .collect();
    let d: usize = v[0].parse().unwrap();
    let n: Vec<char> = v[1].chars().collect();

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let v: Vec<i64> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [dx, dy] = v[..] else { panic!(); };
    let mut x = 0;
    let mut y = 0;
    for i in 0..d {
        x <<= 1;
        y <<= 1;
        if n[i] == '1' || n[i] == '4' { x += 1; }
        if n[i] == '1' || n[i] == '2' { y += 1; }
    }
    println!("origin: {} {}", x, y);

    x += dx;
    y += dy;
    
    println!("target: {} {}", x, y);

    if x < 0 || x >= (1i64 << d) || y < 0 || y >= (1i64 << d) {
        println!("-1");
    } else {
        let mut ret = String::new();
        for _ in 0..d {
            let i = x & 1;
            let j = y & 1;
            x >>= 1;
            y >>= 1;
            if i == 1 && j == 1 { ret += "1"; }
            if i == 0 && j == 1 { ret += "2"; }
            if i == 0 && j == 0 { ret += "3"; }
            if i == 1 && j == 0 { ret += "4"; }
        }
        println!("{}", ret.chars().rev().collect::<String>());
    }
}