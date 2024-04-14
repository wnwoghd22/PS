use std::io;

fn main() {
    let mut s = String::new();
    let mut arr = String::new();

    io::stdin().read_line(&mut s).unwrap();

    let values:Vec<i32> = s
        .as_mut_str()
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    if values[0] == 0 {
        println!("{}", 1);
        return;
    }
    
    io::stdin().read_line(&mut arr).unwrap();
    
    let scores:Vec<i32> = arr
        .as_mut_str()
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let mut order = 0;
    let mut bound = 0;
    for score in scores {
        if score > values[1] { bound += 1; }
        if score >= values[1] { order += 1; }
        if score < values[1] { break; }
    }

    println!("{}", if order >= values[2] as usize {
        -1
    } else {
        bound + 1 as i32
    });
}