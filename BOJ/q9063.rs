use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u32 = s.trim().parse().unwrap();
    let mut min_x = 10000;
    let mut max_x = -10000;
    let mut min_y = 10000;
    let mut max_y = -10000;
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let pos: Vec<i32> = s
            .as_mut_str()
            .split_whitespace()
            .map(|v| v.parse().unwrap())
            .collect();
        let (x, y) = (pos[0], pos[1]);
        if x < min_x { min_x = x; }
        if x > max_x { max_x = x; }
        if y < min_y { min_y = y; }
        if y > max_y { max_y = y; }
    }
    println!("{}", (max_x - min_x) * (max_y - min_y))
}