use std::cmp::Ordering;
use std::fmt;
use std::ops::{Add, Sub, Mul, Div};

// 최대공약수를 구하는 함수
fn gcd(a: i128, b: i128) -> i128 {
    if b == 0 { a } else { gcd(b, a % b) }
}

#[derive(Clone, Copy, Debug)]
struct Fraction {
    num: i128,
    den: i128,
}

impl Fraction {
    fn from(n: i128) -> Self {
        Fraction { n, 1 }
    }

    // 생성자
    fn new(n: i128, d: i128) -> Self {
        let mut num = n;
        let mut den = d;
        if den < 0 {
            num = -num;
            den = -den;
        }
        if num == 0 {
            den = 1;
        }
        Fraction { num, den }.normalize()
    }

    // 분수를 정규화 (약분)
    fn normalize(self) -> Self {
        let g = gcd(self.num.abs(), self.den);
        Fraction { num: self.num / g, den: self.den / g }
    }

    // 역수
    fn inv(self) -> Self {
        Fraction::new(self.den, self.num)
    }
}

// Add trait을 구현하여 + 연산 지원
impl Add for Fraction {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        let d = self.den * other.den / gcd(self.den, other.den);
        let n = self.num * (d / self.den) + other.num * (d / other.den);
        Fraction::new(n, d)
    }
}

// Sub trait을 구현하여 - 연산 지원
impl Sub for Fraction {
    type Output = Self;

    fn sub(self, other: Self) -> Self {
        self + (-other)
    }
}

// Mul trait을 구현하여 * 연산 지원
impl Mul for Fraction {
    type Output = Self;

    fn mul(self, other: Self) -> Self {
        Fraction::new(self.num * other.num, self.den * other.den)
    }
}

// Div trait을 구현하여 / 연산 지원
impl Div for Fraction {
    type Output = Self;

    fn div(self, other: Self) -> Self {
        self * other.inv()
    }
}

// 음수 변환을 위한 Neg trait 구현
impl std::ops::Neg for Fraction {
    type Output = Self;

    fn neg(self) -> Self {
        Fraction::new(-self.num, self.den)
    }
}

// 표시를 위한 Display trait 구현
impl fmt::Display for Fraction {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}/{}", self.num, self.den)
    }
}

fn main() {
    let a = Fraction::new(3, 4);
    let b = Fraction::new(5, 6);
    
    let sum = a + b;
    let diff = a - b;
    let prod = a * b;
    let div = a / b;

    println!("a + b = {}", sum);
    println!("a - b = {}", diff);
    println!("a * b = {}", prod);
    println!("a / b = {}", div);
}