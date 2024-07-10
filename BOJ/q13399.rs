use std::io::{self, BufRead, Write};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());

    let v: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut ord: Vec<i32> = (0..v[0]+1).collect();
    for q in 0..v[1] {
        let x: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        ord[x] = -q;
    }
    let mut arr: Vec<(i32, i32)> = vec![];
    for i in 1..v[0]+1 {
        arr.push((ord[i as usize], i));
    }
    arr.sort();
    for (_, x) in arr {
        _ = writeln!(writer, "{}", x);
    }
    writer.flush().unwrap();
}