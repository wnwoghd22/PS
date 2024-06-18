use std::io::{self, BufRead};
use std::cmp::min;

static INF: i64 = 1e17 as i64;

#[derive(PartialEq, Eq, PartialOrd, Ord, Clone)]
struct Pos {
    x: i64,
    y: i64,
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> i64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();

    let s = iter.next().unwrap().unwrap();
    let v: Vec<i64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = v[0] as usize;
    let pivot = Pos { x: v[1], y: v[2] };
    let mut edges: Vec<(Pos, Pos)> = vec![];
    let mut cost: Vec<i64> = vec![0; n];
    for i in 0..n {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<i64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        let a = Pos { x: v[0], y: v[1] };
        let b = Pos { x: v[2], y: v[3] };
        if ccw(&pivot, &a, &b) > 0 { edges.push((a, b)); }
        else { edges.push((b, a)); }
        cost[i] = v[4];
    }
    let mut dist = vec![vec![INF; n]; n];
    for i in 0..n {
        for j in 0..n {
            if edges[i].1 == edges[j].0 && ccw(&edges[i].0, &edges[i].1, &edges[j].1) > 0 {
                dist[i][j] = cost[i];
            }
        }
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                let d = dist[i][k] + dist[k][j];
                if d < dist[i][j] { dist[i][j] = d; }
            }
        }
    }

    let mut ret = INF;
    for i in 0..n {
        for j in 0..n {
            ret = min(ret, dist[i][j] + dist[j][i]);
        }
    }
    if ret == INF { ret = -1; }
    println!("{}", ret);
}