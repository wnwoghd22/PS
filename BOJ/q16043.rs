use std::io::{self, BufRead, Write};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = v[0];
    let m = v[1];
    let mut a: Vec<bool> = vec![false; n + 1];
    let mut x: Vec<usize> = Vec::with_capacity(m);
    for _ in 0..m {
        let g: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        x.push(g);
        a[g] = true;
    }

    let mut i = 1;
    for j in x {
       while i <= n && i < j {
            if !a[i] {
                _ = writeln!(writer, "{}", i);
            }
            i += 1;
        }
        _ = writeln!(writer, "{}", j);
    }
    while i <= n {
        if !a[i] {
            _ = writeln!(writer, "{}", i);
        }
        i += 1;
    }

    writer.flush().unwrap();
}