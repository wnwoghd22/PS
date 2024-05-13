use std::io;

#[derive(PartialEq, Eq, PartialOrd, Ord, Clone)]
struct Pos {
    x: i64,
    y: i64,
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> i64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn monotone_chain(pos: &Vec<Pos>) -> (Vec<Pos>, Vec<Pos>) {
    let mut lower: Vec<Pos> = Vec::new();
    let mut upper: Vec<Pos> = Vec::new();

    for p in pos {
        while lower.len() > 1 && ccw(&lower[lower.len() - 2], &lower[lower.len() - 1], p) <= 0 {
            lower.pop();
        }
        lower.push(p.clone());
    }

    for p in pos.iter().rev() {
        while upper.len() > 1 && ccw(&upper[upper.len() - 2], &upper[upper.len() - 1], p) <= 0 {
            upper.pop();
        }
        upper.push(p.clone());
    }

    (lower, upper)
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let values: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m] = values[..] else { panic!(); };

    let mut towers: Vec<Pos> = Vec::new();
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let values: Vec<i64> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [x, y] = values[..] else { panic!(); };
        towers.push(Pos { x, y });
    }
    let mut monuments: Vec<Pos> = Vec::new();
    for _ in 0..m {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let values: Vec<i64> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let [x, y] = values[..] else { panic!(); };
        monuments.push(Pos { x, y });
    }
    monuments.sort();
    let (upper, lower) = monotone_chain(&monuments);
}