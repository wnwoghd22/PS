use std::io::{self, BufRead};
use std::mem;

static INF: f64 = 1e17;
static TOL: f64 = 1e-7;

struct Pos {
    x: f64,
    y: f64,
}

fn cross(p1: &Pos, p2: &Pos, p3: &Pos) -> f64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> i32 {
    let c = cross(p1, p2, p3);
    if c < TOL && c > -TOL { 0 }
    else if c > 0.0 { 1 }
    else { -1 }
}

fn dot(p1: &Pos, p2: &Pos, p3: &Pos) -> f64 {
    (p2.x - p1.x) * (p3.x - p2.x) + (p2.y - p1.y) * (p3.y - p2.y)
}

fn on_seg_strong(p1: &Pos, p2: &Pos, q1: &Pos) -> bool {
    let d = dot(p1, q1, p2);
    d > -TOL && ccw(p1, p2, q1) == 0
}

fn on_seg_weak(p1: &Pos, p2: &Pos, q1: &Pos) -> bool {
    let d = dot(p1, q1, p2);
    d > 0.0 && ccw(p1, p2, q1) == 0
}

fn inner_check(h: &Vec<Pos>, p: &Pos) -> bool {
    let mut cnt = 0;
    for i in 0..h.len() {
        let mut p1 = &h[i];
        let mut p2 = &h[(i + 1) % h.len()];
        if on_seg_strong(p1, p2, p) { return true; }
        if p1.y - p2.y < TOL && p1.y - p2.y > -TOL { continue; }
        if p1.y > p2.y { mem::swap(&mut p1, &mut p2); }
        if p.y + TOL > p2.y || p.y < p1.y { continue; }
        if ccw(p1, p2, p) > 0 { cnt += 1; }
    }
    cnt & 1 == 1
}

fn intersect(p1: &Pos, p2: &Pos, q1: &Pos, q2: &Pos) -> bool {
    ccw(p1, p2, q1) * ccw(p1, p2, q2) < 0 && ccw(q1, q2, p1) * ccw(q1, q2, p2) < 0
}

fn blocked(h: &Vec<Pos>, q1: &Pos, q2: &Pos) -> bool {
    for i in 0..h.len() {
        let p1 = &h[i];
        let p2 = &h[(i + 1) % h.len()];
        if intersect(p1, p2, q1, q2) || on_seg_weak(q1, q2, p1) || on_seg_weak(q1, q2, p2) {
            return true;
        }
    }
    false
}

fn connectable(p1: &Pos, p2: &Pos, inner: &Vec<Pos>, outer: &Vec<Pos>) -> bool {
    let mid = Pos {
        x: (p1.x + p2.x) * 0.5,
        y: (p1.y + p2.y) * 0.5,
    };
    !blocked(inner, p1, p2) && !blocked(outer, p1, p2) && inner_check(outer, &mid) && !inner_check(inner, &mid)
}

fn euc(p1: &Pos, p2: &Pos) -> f64 {
    ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)).sqrt()
}

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();

    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut inner: Vec<Pos> = vec![];
    for _ in 0..n {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<f64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        inner.push(Pos { x: v[0], y: v[1] });
    }

    let m: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    let mut outer: Vec<Pos> = vec![];
    for _ in 0..m {
        let s = iter.next().unwrap().unwrap();
        let v: Vec<f64> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        outer.push(Pos { x: v[0], y: v[1] });
    }

    let mut dist = vec![vec![INF; n + m]; n + m];
    for i in 0..n {
        dist[i][(i + 1) % n] = euc(&inner[i], &inner[(i + 1) % n]);
        for j in 0..n {
            if (ccw(&inner[i], &inner[(i + 1) % n], &inner[j]) > 0 ||
                on_seg_weak(&inner[i], &inner[j], &inner[(i + 1) % n])) &&
                connectable(&inner[(i + 1) % n], &inner[j], &inner, &outer) {
                dist[(i + 1) % n][j] = euc(&inner[j], &inner[(i + 1) % n]);
            }
        }
        for j in 0..m {
            if (ccw(&inner[i], &inner[(i + 1) % n], &outer[j]) > 0 ||
                on_seg_weak(&inner[i], &outer[j], &inner[(i + 1) % n])) &&
                connectable(&inner[(i + 1) % n], &outer[j], &inner, &outer) {
                dist[(i + 1) % n][j + n] = euc(&outer[j], &inner[(i + 1) % n]);
            }
        }
    }
    for i in 0..m {
        dist[i + n][(i + 1) % m + n] = euc(&outer[i], &outer[(i + 1) % m]);
        for j in 0..n {
            if (ccw(&outer[i], &outer[(i + 1) % m], &inner[j]) < 0 ||
                on_seg_weak(&outer[i], &inner[j], &outer[(i + 1) % m])) &&
                connectable(&outer[(i + 1) % m], &inner[j], &inner, &outer) {
                dist[(i + 1) % m + n][j] = euc(&inner[j], &outer[(i + 1) % m]);
            }
        }
        for j in 0..m {
            if (ccw(&outer[i], &outer[(i + 1) % m], &outer[j]) < 0 ||
                on_seg_weak(&outer[i], &outer[j], &outer[(i + 1) % m])) &&
                connectable(&outer[(i + 1) % m], &outer[j], &inner, &outer) {
                dist[(i + 1) % m + n][j + n] = euc(&outer[j], &outer[(i + 1) % m]);
            }
        }
    }

    for k in 0..n+m {
        for i in 0..n+m {
            for j in 0..n+m {
                let d = dist[i][k] + dist[k][j];
                if d < dist[i][j] { dist[i][j] = d; }
            }
        }
    }

    let mut pivot = 0;
    for i in 1..n {
        if inner[i].y < inner[pivot].y {
            pivot = i;
        }
    }

    let mut hull: Vec<usize> = vec![];
    let mut origin = pivot;
    loop {
        hull.push(origin);
        let mut x = (origin + 1) % n;
        for k in 0..n {
            if ccw(&inner[origin], &inner[x], &inner[k]) < 0 {
                x = k;
            }
        }
        if x == pivot { break; }
        origin = x;
    }

    let mut ret = 0.0;
    for i in 0..hull.len() {
        ret += dist[hull[i]][hull[(i + 1) % hull.len()]];
    }
    println!("{}", ret);
}