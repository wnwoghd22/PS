use std::io::{self, BufRead};

struct Pos {
    x: i64,
    y: i64,
}

fn cross(p1: &Pos, p2: &Pos, p3: &Pos) -> i64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut pos: Vec<Pos> = vec![];
    for _ in 0..n {
        let v: Vec<i64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        pos.push(Pos { x: v[0], y: v[1] });
    }
    let zero = Pos { x: 0, y: 0 };
    let mut sum = 0;
    for i in 0..n {
        let j = (i + 1) % n;
        sum += cross(&zero, &pos[i], &pos[j]);
    }
    let mut area = sum.abs() as f64 / 2;
    area *= 1.0 - std::f64::consts::PI / 3f64.sqrt() / 3.0;
    println!("{:.9}", area / 3.0);
}