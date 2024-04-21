use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no testcase");
    let t: u32 = s.trim().parse().expect("not a number");

    for _ in 0..t {
        let mut ss = String::new();
        io::stdin().read_line(&mut ss).expect("no input");
        let mut n: u32 = ss.trim().parse().expect("not a number");
        
        let quarter = n / 25; n %= 25;
        let dime = n / 10; n %= 10;
        let nickel = n / 5; n %= 5;
        let penny = n;

        println!("{quarter} {dime} {nickel} {penny}");
    }
}