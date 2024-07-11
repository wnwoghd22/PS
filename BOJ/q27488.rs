use std::io::{self, BufRead, Write};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());
    
    let tc: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..tc {
        let n: u32 = iter.next().unwrap().unwrap().trim().parse().unwrap();
    
        let mut v: Vec<u32> = vec![];
        let mut k = n;
        while k > 0 {
            v.push(k % 10);
            k /= 10;
        }
        let mut x = 0;
        let mut y = 0;
        let mut z = 0;
        for d in v.iter().rev() {
            x = x * 10 + d / 2;
            y = y * 10 + d / 2;
            if d % 2 == 1 {
                x += z;
                y += 1 - z;
                z = 1 - z;
            }
        }
        assert!(x + y == n);
        _ = writeln!(writer, "{} {}", x, y);
    }
    writer.flush().unwrap();
}