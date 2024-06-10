use std::io;
use std::cmp::min;

static MOD: i64 = 1 << 30;

struct Mu {
    mu: Vec<i64>,
    s: Vec<i64>,
}

impl Mu {
    fn init(len: usize) -> Self {
        let mut mu: Vec<i64> = vec![0; len + 1];
        let mut s: Vec<i64> = vec![0; len + 1];
        mu[1] = 1;
        for i in 1..len+1 {
            s[i] = (s[i] + (i as i64) * (MOD + mu[i])) % MOD;
            s[i] = ((i as i64) * s[i] + s[i - 1]) % MOD;
            if mu[i] == 0 { continue; }
            for j in (i*2..len+1).step_by(i) {
                mu[j] -= mu[i];
                s[j] = (s[j] + (i as i64) * (MOD + mu[i])) % MOD;
            }
        }

        Mu {
            mu,
            s,
        }
    }

    fn g(&self, n: i64, m: i64) -> i64 {
        let mut ret: i64 = 0;
        let len = min(n, m);
        let mut i = 1;
        while i <= len {
            let j = min(n / (n / i), m / (m / i));
            let sum1 = (n / i) * (n / i + 1) / 2 % MOD;
            let sum2 = (m / i) * (m / i + 1) / 2 % MOD;
            ret += sum1 * sum2 % MOD * (self.s[j as usize] - self.s[(i - 1) as usize] + MOD) % MOD;
            ret %= MOD;
            i = j + 1;
        }
        ret
    }

    fn f(&self, n: i64, m: i64) -> i64 { // TODO: need to fix
        let mut ret: i64 = 0;
        let len = min(n, m);
        let mut x = 1;
        while x * x <= len {
            ret = (ret + (MOD + self.mu[x as usize]) * (x * x) % MOD * self.g(n / (x * x), m / (x * x))) % MOD;
            x += 1;
        }
        ret
    }
}

fn main() {
    let mu = Mu::init(4_000_000);
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let t: u32 = s.trim().parse().unwrap();
    for _ in 0..t {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<i64> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        println!("{}", mu.f(v[0], v[1]));
    }
}