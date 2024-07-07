use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u64 = s.trim().parse().unwrap();
    let mut sl = n;
    let mut sr = n + 1;
    let mut l = n + 1;
    let mut r = n + 1;
    loop {
        // println!("{} {} {} {}", l, r, sl, sr);
        sr -= l;
        l += 1;
        while sr < sl {
            r += 1;
            sr += r;
        }
        if sr == sl {
            println!("{} {} {}", n, l - 1, r);
            break;
        }
        sl += l - 1;
    }
}