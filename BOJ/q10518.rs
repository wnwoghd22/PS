use std::io::{self, BufRead};

static INF: f64 = 1e17;
static TOL: f64 = 1e-7;

struct Pos {
    x: f64,
    y: f64,
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> f64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn dot(p1: &Pos, p2: &Pos, p3: &Pos) -> f64 {
    (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y)
}

fn intersect(p1: &Pos, p2: &Pos, q1: &Pos, q2: &Pos) -> bool {
    ccw(p1, p2, q1) * ccw(p1, p2, q2) < TOL && ccw(q1, q2, p1) * ccw(q1, q2, p2) < TOL
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
            if ccw(&inner[i], &inner[(i + 1) % n], &inner[j]) < 0.0 && 
                dot(&inner[i], &inner[(i + 1) % n], &inner[j]) > 0.0 {
                let mut valid = true;
                for k in 0..n {
                    let l = (k + 1) % n;
                    if k == i || k == j || l == i || l == j { continue; }
                    if intersect(&inner[i], &inner[j], &inner[k], &inner[l]) {
                        valid = false;
                        break;
                    }
                }
                for k in 0..m {
                    let l = (k + 1) % m;
                    if intersect(&inner[i], &inner[j], &outer[k], &outer[l]) {
                        valid = false;
                        break;
                    }
                }
                if valid { dist[i][j] = euc(&inner[i], &inner[j]); }
            }
        }
        for j in 0..m {
            if ccw(&inner[i], &inner[(i + 1) % n], &outer[j]) < 0.0 && 
                dot(&inner[i], &inner[(i + 1) % n], &outer[j]) > 0.0 {
                let mut valid = true;
                for k in 0..n {
                    let l = (k + 1) % n;
                    if k == i || l == i { continue; }
                    if intersect(&inner[i], &outer[j], &inner[k], &inner[l]) {
                        valid = false;
                        break;
                    }
                }
                for k in 0..m {
                    let l = (k + 1) % m;
                    if k == j || l == j { continue; }
                    if intersect(&inner[i], &outer[j], &outer[k], &outer[l]) {
                        valid = false;
                        break;
                    }
                }
                if valid { dist[i][j + n] = euc(&inner[i], &outer[j]); }
            }
        }
    }

    for i in 0..m {
        dist[i + n][(i + 1) % m + n] = euc(&outer[i], &outer[(i + 1) % m]);
        for j in 0..n {
            if ccw(&outer[(i + m - 1) % m], &outer[i], &inner[j]) < 0.0 {
                let mut valid = true;
                for k in 0..n {
                    let l = (k + 1) % n;
                    if k == j || l == j { continue; }
                    if intersect(&outer[i], &inner[j], &inner[k], &inner[l]) {
                        valid = false;
                        break;
                    }
                }
                for k in 0..m {
                    let l = (k + 1) % m;
                    if k == i || l == i { continue; }
                    if intersect(&outer[i], &inner[j], &outer[k], &outer[l]) {
                        valid = false;
                        break;
                    }
                }
                if valid { dist[i + n][j] = euc(&outer[i], &inner[j]); }
            }
        }
        for j in 0..m {
            if ccw(&outer[(i + m - 1) % m], &outer[i], &outer[j]) < 0.0 && 
                ccw(&outer[i], &outer[(i + 1) % m], &outer[j]) > 0.0 {
                let mut valid = true;
                for k in 0..n {
                    if intersect(&outer[i], &outer[j], &inner[k], &inner[(k + 1) % n]) {
                        valid = false;
                        break;
                    }
                }
                for k in 0..m {
                    if intersect(&outer[i], &outer[j], &outer[k], &outer[(k + 1) % m]) {
                        valid = false;
                        break;
                    }
                }
                let mid = Pos {
                    x: (outer[i].x + outer[j].x) / 2.0,
                    y: (outer[i].y + outer[j].y) / 2.0,
                };
                let border = Pos {
                    x: mid.x,
                    y: 5001f64,
                };

                let mut cnt = 0;
                for k in 0..m {
                    if intersect(&mid, &border, &outer[k], &outer[(k + 1) % m]) {
                        cnt += 1;
                    }
                }
                if cnt & 1 == 0 { valid = false; }

                if valid { dist[i + n][j + n] = euc(&outer[i], &outer[j]); }
            }
        }
    }
    
    for i in 0..n+m {
        for j in 0..n+m {
            if dist[i][j] > INF - 100.0 { print!("-1 ") }
            else { print!("{} ", dist[i][j]); }
        }
        println!("");
    }

    for k in 0..n+m {
        for i in 0..n+m {
            for j in 0..n+m {
                let d = dist[i][k] + dist[k][j];
                if d < dist[i][j] { dist[i][j] = d; }
            }
        }
    }

    let mut ret = INF;
    for i in 0..n+m {
        for j in 0..n+m {
            ret = f64::min(ret, dist[i][j] + dist[j][i]);
        }
    }
    println!("{}", ret);
}