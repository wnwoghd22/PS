use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let arr: Vec<i32> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (p1, p2, p3) = (arr[0], arr[1], arr[2]);
    let (x1, x2, x3) = (arr[3], arr[4], arr[5]);
    for x in (x1..=p1*p2*p3).step_by(p1 as usize) {
        if x % p2 == x2 && x % p3 == x3 {
            println!("{}", x);
            return;
        }
    }
    println!("-1");
}