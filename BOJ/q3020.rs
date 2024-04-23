use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let (n, h) = (values[0], values[1]);

    let mut l = vec![0; h + 1];
    let mut r = vec![0; h + 1];
    
    for i in 0..n {
        let mut x = String::new();
        io::stdin().read_line(&mut x).unwrap();
        let a: usize = x.trim().parse().unwrap();
        if i & 1 == 0 {
            l[a] += 1;
        } else {
            r[h - a + 1] += 1;
        }
    }
    for i in (0..h).rev() {
        l[i] += l[i + 1];
    }
    for i in 0..h {
        r[i + 1] += r[i];
    }
    let mut min = n;
    let mut cnt = 0;
    for i in 1..h+1 {
        if l[i] + r[i] == min {
            cnt += 1;
        }
        else if l[i] + r[i] < min {
            min = l[i] + r[i];
            cnt = 1;
        }
    }
    println!("{} {}", min, cnt);
}