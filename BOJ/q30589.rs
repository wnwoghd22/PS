use std::io::{self, BufRead};

struct Pos {
    x: f64,
    y: f64,
}

fn euc(p1: &Pos, p2: &Pos) -> f64 {
    ((p1.x - p2.x) * (p1.x - p2.x) +
    (p1.y - p2.y) * (p1.y - p2.y)).sqrt()
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut pos: Vec<Pos> = vec![];
    for _ in 0..n {
        let v: Vec<f64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        pos.push(Pos { x: v[0], y: v[1] });
    }
    let mut sum = 0.0;
    let mut max = 0.0;
    for i in 0..n {
        let j = (i + 1) % n;
        let w = euc(&pos[i], &pos[j]);
        sum += w;
        if w > max { max = w; }
    }
    println!("{:.9}", sum - max);
}