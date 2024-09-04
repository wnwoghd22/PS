use std::io;

fn ctoi(c: u8) -> u8 { c - if c >= b'0' && c <= b'9' { b'0' } else { b'A' - 10 } }

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let d: Vec<u8> = s.trim().bytes().collect();
    let mut eff = 1u64;
    let mut ret = 0u64;
    for &c in d.iter().rev() {
        ret += ctoi(c) as u64 * eff;
        eff *= 16;
    }
    println!("{}", ret);
}