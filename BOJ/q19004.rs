use std::io::{self, BufRead, Write};
use std::cmp::Ordering;
use std::ops::Neg;

#[derive(Debug, Clone, Copy)]
struct Rational(i128, i128);

impl Rational {
    fn normalize(&self) -> Self {
        let gcd = gcd(self.0, self.1);
        let num = self.0 / gcd;
        let den = self.1 / gcd;
        if den < 0 {
            Rational(-num, -den)
        } else {
            Rational(num, den)
        }
    }
}

fn gcd(a: i128, b: i128) -> i128 {
    if b == 0 {
        a.abs()
    } else {
        gcd(b, a % b)
    }
}

impl Neg for Rational {
    type Output = Self;

    fn neg(self) -> Self::Output {
        Rational(-self.0, self.1).normalize()
    }
}

impl PartialEq for Rational {
    fn eq(&self, other: &Self) -> bool {
        let normalized_self = self.normalize();
        let normalized_other = other.normalize();
        normalized_self.0 == normalized_other.0 && normalized_self.1 == normalized_other.1
    }
}

impl Eq for Rational {}

impl PartialOrd for Rational {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let lhs = self.0 * other.1;
        let rhs = other.0 * self.1;
        lhs.partial_cmp(&rhs)
    }
}

impl Ord for Rational {
    fn cmp(&self, other: &Self) -> Ordering {
        self.partial_cmp(other).unwrap()
    }
}

struct FenwickTree {
    tree: Vec<i64>,
    size: usize,
}

impl FenwickTree {
    pub fn new(size: usize) -> Self {
        FenwickTree {
            tree: vec![0; size + 1],
            size,
        }
    }

    pub fn sum(&self, idx: usize) -> i64 {
        let mut sum = 0;
        let mut i = idx as isize;
        while i > 0 {
            sum += self.tree[i as usize];
            i -= i & -i;
        }
        sum
    }

    pub fn add(&mut self, idx: usize, value: i64) {
        let mut i = idx as isize;
        while (i as usize) <= self.size {
            self.tree[i as usize] += value;
            i += i & -i;
        }
    }
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());

    let t: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let v: Vec<i128> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let (n, x1, y1, x2, y2) = (v[0] as usize, v[1], v[2], v[3], v[4]);

        let mut seg: Vec<(usize, usize)> = vec![(0, 0); n];
        let mut pos: Vec<(i32, Rational, usize, usize)> = vec![];
        for i in 0..n {
            let v: Vec<i128> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            let (a, b) = (v[0], v[1]);
            let p1 = Rational(y2 - b, a);
            let mut dir = 0;
            if Rational(x1, 1) < p1 && p1 <= Rational(x2, 1) {
                pos.push((1, -p1, i, dir));
                dir += 1;
            }
            let p2 = Rational(a * x1 + b, 1);
            if y1 < p2.0 && p2.0 <= y2 {
                pos.push((2, -p2, i, dir));
                dir += 1;
            }
            let p3 = Rational(y1 - b, a);
            if Rational(x1, 1) <= p3 && p3 < Rational(x2, 1) {
                pos.push((3, p3, i, dir));
                dir += 1;
            }
            let p4 = Rational(a * x2 + b, 1);
            if y1 <= p4.0 && p4.0 < y2 {
                pos.push((4, p4, i, dir));
                // dir += 1;
            }
        }
        pos.sort();

        println!("{:?}", pos);

        let mut idx = 1;
        seg[pos[0].2].0 = idx;
        seg[pos[0].2].1 = idx;
        for i in 1..pos.len() {
            if pos[i].0 != pos[i - 1].0 || pos[i].1 != pos[i- 1].1 { idx += 1; }
            seg[pos[i].2].1 = idx;
            if pos[i].3 == 0 {
                seg[pos[i].2].0 = idx;
            }
        }
        seg.sort();

        println!("{:?}", seg);

        let mut f = FenwickTree::new(idx);
        let mut ret: i64 = 0;
        for (l, r) in seg {
            if l == 0 { continue; }
            ret += f.sum(r) - f.sum(l - 1);
            f.add(r, 1);
        }
        _ = writeln!(writer, "{}", ret);
    }

    writer.flush().unwrap();
}