use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let mut t = String::new();
    io::stdin().read_line(&mut t).unwrap();
    
    let vs: Vec<char> = s.trim().chars().collect();
    let vt: Vec<char> = t.trim().chars().collect();

    println!("{:?}", vt);

    let mut st: Vec<char> = vec!['$'; vs.len() + 1];
    let mut sp = 0;
    'reading:
    for c in vs {
        st[sp] = c;
        sp += 1;
        println!("{} {:?}", sp, st);
        if sp >= vt.len() {
            '_matching:
            for i in 0..vt.len() {
                if st[sp - vt.len() + i] != vt[i] {
                    continue 'reading;
                }
            }
            println!("found!");
            sp -= vt.len();
        }
    }
    println!("{}", st[..sp].iter().collect::<String>());
}