use std::io;

struct Dice {
    l: u32,
    r: u32,
    u: u32,
    d: u32,
    f: u32,
    b: u32,
}

impl Dice {
    fn new() -> Dice {
        Dice {
            l: 0,
            r: 0,
            u: 0,
            d: 0,
            f: 0,
            b: 0,
        }
    }

    fn rotate(&mut self, dir: u32) {
        match dir {
            1 => {
                let temp = self.u;
                self.u = self.l;
                self.l = self.d;
                self.d = self.r;
                self.r = temp;
            }
            2 => {
                let temp = self.u;
                self.u = self.r;
                self.r = self.d;
                self.d = self.l;
                self.l = temp;
            }
            3 => {
                let temp = self.u;
                self.u = self.f;
                self.f = self.d;
                self.d = self.b;
                self.b = temp;
            }
            4 => {
                let temp = self.u;
                self.u = self.b;
                self.b = self.d;
                self.d = self.f;
                self.f = temp;
            }
            _ => (),
        }
    }

    fn u(&self) -> u32 {
        self.u
    }
    
    fn d(&self) -> u32 {
        self.d
    }

    fn set_d(&mut self, n: u32) {
        self.d = n;
    }
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m, x, y, _k] = v[..] else { panic!(); };
    
    let mut map: Vec<Vec<u32>> = vec![];
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<u32> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        map.push(v);
    }

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let dirs: Vec<u32> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut r = x;
    let mut c = y;
    let mut dice = Dice::new();
    for d in dirs {
        if d == 1 {
            if c == m - 1 {
                continue;
            }
            else {
                c += 1;
            }
        }
        if d == 2 {
            if c == 0 {
                continue;
            }
            else {
                c -= 1;
            }
        }
        if d == 3 {
            if r == 0 {
                continue;
            }
            else {
                r -= 1;
            }
        }
        if d == 4 {
            if r == n - 1 {
                continue;
            }
            else {
                r += 1;
            }
        }
        
        dice.rotate(d);
        if map[r][c] == 0 {
            map[r][c] = dice.d();
        }
        else {
            dice.set_d(map[r][c]);
            map[r][c] = 0;
        }
        println!("{}", dice.u());
    }
}