use std::io;

fn main() {
    let mut n = 0;
    let mut arr:Vec<Vec<char>> = Vec::new();
    for _ in 0..5 {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        if s.len() > n {
            n = s.len();
        }
        arr.push(s.trim().chars().collect());
    }
    for i in 0..n {
        for a in &arr {
            if a.len() <= i {
                continue;
            }
            print!("{}", a[i] as char);
        }
    }
}