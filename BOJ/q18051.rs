use std::io::{self, BufRead, Write};
use std::cmp::Ordering;

#[derive(Debug, Clone)]
struct Pos {
    x: i64,
    y: i64,
}

fn cross(p1: &Pos, p2: &Pos, p3: &Pos) -> i64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> i32 {
    let c = cross(p1, p2, p3);
    if c == 0 { 0 }
    else if c > 0 { 1 }
    else { -1 }
}

fn intersect(p1: &Pos, p2: &Pos, q1: &Pos, q2: &Pos) -> bool {
    ccw(p1, p2, q1) * ccw(p1, p2, q2) < 0 && ccw(q1, q2, p1) * ccw(q1, q2, p2) < 0
}

fn merge_sort(arr: &mut Vec<Pos>, tmp: &mut Vec<Pos>, pvt: &Pos) -> i64 {

    0
}

fn query(p1: &Pos, p2: &Pos, p3: &Pos, p4: &Pos, ant: &mut Vec<Pos>) -> i64 {
    let mut tmp: Vec<Pos> = vec![Pos { x: 0, y: 0 }; ant.len()];
    merge_sort(ant, &mut tmp, p1);
    let x = merge_sort(ant, &mut tmp, p3);

    // merge_sort(ant, &mut tmp, )

    0
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let z: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..z {
        iter.next(); // empty line

        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut hull: Vec<Pos> = vec![];
        for _ in 0..n {
            let v: Vec<i64> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            hull.push(Pos { x: v[0], y: v[1]});
        }

        let m: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut ant: Vec<Pos> = vec![];
        for _ in 0..m {
            let v: Vec<i64> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            ant.push(Pos { x: v[0], y: v[1]});
        }
        
        let q: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        for _ in 0..q {
            let v: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            _ = write!(writer, "{} ", 
                query(
                    &hull[v[0]], &hull[(v[0] + 1) % n],
                    &hull[v[1]], &hull[(v[1] + 1) % n],
                    &mut ant,
                )
            );
        }
        _ = writeln!(writer); 
    }
    writer.flush().unwrap();
}