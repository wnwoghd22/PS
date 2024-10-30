use std::io;
fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let arr: Vec<i64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    for i in 1..=1000000 {
        let mut cnt = 0;
        for &a in &arr {
            if i % a == 0 {
                cnt += 1;
            }
        } 
        if cnt >= 3 {
            println!("{}", i);
            break;
        }
    }
}