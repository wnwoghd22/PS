use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<u64> = s.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let [n, m] = v[..] else { panic!(); };

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let v: Vec<u64> = ss.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let [x, y] = v[..] else { panic!(); };

    let mut digits = 9;
    let mut fixed_d = 0;
    let mut pos = n;
    for _ in 0..m {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<u64> = s.as_mut_str().split_whitespace().map(|x| x.parse().unwrap()).collect();
        let [a, _b] = v[..] else { panic!(); };
        digits -= 1;
        pos -= 1;
        if a == 0 { fixed_d += 1; }
    }

    let mut ret = 1;
    for k in 0..fixed_d {
        ret *= pos + fixed_d - k;
    }
    for k in 0..pos {
        ret *= digits - k;
    }
    let cost = x * ret + y * ((ret + 2) / 3 - 1);

    println!("{}", cost);
}