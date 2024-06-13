use std::io;

static BESSIE: [char; 6] = ['b', 'e', 's', 's', 'i', 'e'];

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let s: Vec<char> = s.trim().chars().collect();

    let mut pre: Vec<u64> = vec![0; 7];
    let mut ret = 0;
    let mut suf = s.len() as u64;
    for c in s {
        pre[0] += 1;
        for i in (0..6).rev() {
            if c == BESSIE[i] {
                pre[i + 1] += pre[i];
                pre[i] = 0;
            }
        }
        ret += pre[6] * suf;
        suf -= 1;
        pre[0] += pre[6];
        pre[6] = 0;

        println!("{:?}", pre);
    }
    println!("{}", ret);
}