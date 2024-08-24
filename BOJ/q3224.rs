use std::io::{self, BufRead, Write};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let _n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let arr: Vec<i32> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut stack: Vec<(i32, i32)> = vec![];
    // let mut ret: Vec<(i32, i32)> = vec![];

    for a in arr {
        let mut l = a;
        let mut r = a;
        while let Some((s, e)) = stack.pop() {
            if r + 1 == s { 
                r = e; 
            } else if l - 1 == e { 
                l = s; 
            } else {
                stack.push((s, e));
                break;
            }
            // ret.push((l, r));
            _ = writeln!(writer, "{} {}", l , r);
        }
        stack.push((l, r));
    }
    if stack.len() != 1 {
        println!("NE");
        // _ = write!(writer, "NE");
    } else {
        println!("DA");
        writer.flush().unwrap();
        // _ = writeln!(writer, "DA");
        // for (l, r) in ret {
        //     _ = writeln!(writer, "{} {}", l , r);
        // }
    }
    // writer.flush().unwrap();
}