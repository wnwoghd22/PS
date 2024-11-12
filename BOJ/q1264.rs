use std::io;

fn main() {
    let vowels = ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'];
    loop {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        if s.trim() == "#" { break; }
        println!("{}", s.chars()
        .filter(|c| vowels.contains(c))
        .count());
    }
}