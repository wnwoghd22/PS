use std::io;

fn solve() -> u32 {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m] = v[..] else { panic!(); };

    let mut chk: Vec<bool> = vec![false; n + 1];
    let mut arr: Vec<(usize, usize)> = vec![];
    for _ in 0..m {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<usize> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        arr.push((v[1], v[0]));
    }
    arr.sort();
    let mut ret = 0;

    for (r, l) in arr {
        for i in l..r+1 {
            if !chk[i] {
                chk[i] = true;
                ret += 1;
                break;
            }
        }
    }

    ret
}


fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let t: usize = s.trim().parse().unwrap();
    for _ in 0..t {
        println!("{}", solve());
    }
}