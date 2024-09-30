use std::io::{self, BufRead, Write};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let v: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, q) = (v[0], v[1] as usize);
    let mut r = 0;
    let mut c = 0;
    let a: Vec<i64> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut ans: Vec<i64> = vec![];
    if a[0] == n {
        r += 1;
        ans.push(1);
        for i in 1..q {
            let d = a[i] - a[i - 1];
            let x = n - 2 * c;
            let y = n - 2 * r;
            println!("{} {} {}", d, x, y);
            if r < n {
                if d == x {
                    r += 1;
                    ans.push(r);
                    continue;
                }
            }
            if r > 0 {
                if d == -x {
                    ans.push(r);
                    r -= 1;
                    continue;
                }
            }
            if c < n {
                if d == y {
                    c += 1;
                    ans.push(-c);
                    continue;
                }
            }
            if c > 0 {
                if d == -y {
                    ans.push(-c);
                    c -= 1;
                    continue;
                }
            }
            ans.clear();
            break;
        }
    }
    if ans.len() == 0 {
        _ = write!(writer, "-1");
    } else {
        for cmd in ans {
            _ = writeln!(writer, "{} {}", if cmd > 0 { "R" } else { "C" }, cmd.abs());
        }
    }
    writer.flush().unwrap();
}