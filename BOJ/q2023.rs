use std::io;

fn is_prime(x: u32) -> bool {
    for i in 2..x {
        if i * i > x {
            break;
        }
        if x % i == 0 {
            return false;
        }
    }
    return true;
}

fn dfs(x: u32, d: u32, n: u32) {
    if d == n {
        println!("{}", x);
        return;
    }
    for k in [1, 3, 7, 9] {
        let y = x * 10 + k;
        if is_prime(y) {
            dfs(y, d + 1, n);
        }
    }
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: u32 = s.trim().parse().unwrap();
    for k in [2, 3, 5, 7] {
        dfs(k, 1, n);
    }
}