use std::io;

fn main() {
    let mut v: Vec<u32> = vec![];
    for _ in 0..3 {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        v.push(s.trim().parse().unwrap());
    }
    let sum = v[0] + v[1] + v[2];
    if sum != 180 {
        println!("Error");
    } else if v[0] == v[1] && v[1] == v[2] {
        println!("Equilateral");
    } else if v[0] == v[1] || v[1] == v[2] || v[2] == v[0] {
        println!("Isosceles");
    } else {
        println!("Scalene");
    }
}