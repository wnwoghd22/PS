use std::io::{self, BufRead};
use std::collections::BinaryHeap;
use std::cmp::Ordering;

static INF: f64 = 1e17;

#[derive(Debug)]
struct Pos {
    x: i64,
    y: i64,
}

#[derive(Debug)]
struct Seg {
    p1: Pos,
    p2: Pos,
}

#[derive(Copy, Clone, PartialEq, PartialOrd)]
struct Node {
    d: f64,
    u: usize,
}

impl Eq for Node {}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.d.partial_cmp(&self.d).unwrap()
    }
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

fn blocked(h: &Vec<Seg>, q1: &Pos, q2: &Pos) -> bool {
    for i in 0..h.len() {
        let p1 = &h[i].p1;
        let p2 = &h[i].p2;
        if intersect(p1, p2, q1, q2) {
            return true;
        }
    }
    false
}

fn euc(p1: &Pos, p2: &Pos) -> f64 {
    (((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) as f64).sqrt()
}

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();

    let vars: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, m) = (vars[0], vars[1]);

    let mut people: Vec<Pos> = vec![];
    let mut vel: Vec<i64> = vec![];
    for _ in 0..n {
        let s: Vec<String> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.to_owned()).collect();

        // println!("{:?}", s);

        let p: Vec<i64> = s[0][1..s[0].len()-1].split(',').map(|x| x.parse().unwrap()).collect();
        let v: i64 = s[1].trim().parse().unwrap();

        people.push(Pos {
            x: p[0],
            y: p[1],
        });
        vel.push(v);
    }

    let mut walls: Vec<Seg> = vec![];
    for _ in 0..m {
        let s: Vec<String> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.to_owned()).collect();

        // println!("{:?}", s);

        let p1: Vec<i64> = s[0][1..s[0].len()-1].split(',').map(|x| x.parse().unwrap()).collect();
        let p2: Vec<i64> = s[2][1..s[2].len()-1].split(',').map(|x| x.parse().unwrap()).collect();
        
        walls.push(Seg {
            p1: Pos {
                x: p1[0],
                y: p1[1],
            },
            p2: Pos {
                x: p2[0],
                y: p2[1],
            }
        });
    }

    // println!("{:?}", people);
    // println!("{:?}", walls);

    let mut dist: Vec<Vec<(f64, usize)>> = vec![vec![]; 1 + n + m * 2];
    for i in 0..n {
        let target = Pos {
            x: people[i].x,
            y: 0,
        };
        if !blocked(&walls, &people[i], &target) {
            dist[0].push((euc(&people[i], &target), i + 1));
            dist[i + 1].push((euc(&people[i], &target), 0));
        }
    }
    for j in 0..m {
        let j1 = n + 1 + j * 2;
        let j2 = j1 + 1;

        dist[j1].push((euc(&walls[j].p1, &walls[j].p2), j2));
        dist[j2].push((euc(&walls[j].p1, &walls[j].p2), j1));

        let target1 = Pos {
            x: walls[j].p1.x,
            y: 0,
        };
        if !blocked(&walls, &walls[j].p1, &target1) {
            dist[0].push((euc(&walls[j].p1, &target1), j1));
            dist[j1].push((euc(&walls[j].p1, &target1), 0));
        }
        
        let target2 = Pos {
            x: walls[j].p2.x,
            y: 0,
        };
        if !blocked(&walls, &walls[j].p2, &target2) {
            dist[0].push((euc(&walls[j].p2, &target2), j2));
            dist[j2].push((euc(&walls[j].p2, &target2), 0));
        }
    }

    for i in 0..n {
        for j in 0..m {
            let j1 = n + 1 + j * 2;
            let j2 = j1 + 1;

            if !blocked(&walls, &walls[j].p1, &people[i]) {
                dist[i + 1].push((euc(&walls[j].p1, &people[i]), j1));
                dist[j1].push((euc(&walls[j].p1, &people[i]), i + 1));
            }
            
            if !blocked(&walls, &walls[j].p2, &people[i]) {
                dist[i + 1].push((euc(&walls[j].p2, &people[i]), j2));
                dist[j2].push((euc(&walls[j].p2, &people[i]), i + 1));
            }
        }
    }

    for j in 0..m {
        let j1 = n + 1 + j * 2;
        let j2 = j1 + 1;
        for k in 0..m {
            if j == k { continue; }
            let k1 = n + 1 + k * 2;
            let k2 = k1 + 1;

            if !blocked(&walls, &walls[j].p1, &walls[k].p1) {
                dist[j1].push((euc(&walls[j].p1, &walls[k].p1), k1));
                dist[k1].push((euc(&walls[j].p1, &walls[k].p1), j1));
            }
            
            if !blocked(&walls, &walls[j].p2, &walls[k].p1) {
                dist[j2].push((euc(&walls[j].p2, &walls[k].p1), k1));
                dist[k1].push((euc(&walls[j].p2, &walls[k].p1), j2));
            }

            if !blocked(&walls, &walls[j].p1, &walls[k].p2) {
                dist[j1].push((euc(&walls[j].p1, &walls[k].p2), k2));
                dist[k2].push((euc(&walls[j].p1, &walls[k].p2), j1));
            }

            if !blocked(&walls, &walls[j].p2, &walls[k].p2) {
                dist[j2].push((euc(&walls[j].p2, &walls[k].p2), k2));
                dist[k2].push((euc(&walls[j].p2, &walls[k].p2), j2));
            }
        }
    }

    let mut dp: Vec<f64> = vec![INF; 1 + n + m * 2];
    let mut pq: BinaryHeap<Node> = BinaryHeap::new();
    pq.push(Node {
        d: 0.,
        u: 0,
    });
    dp[0] = 0.;
    while let Some(Node { d, u }) = pq.pop() {
        if dp[u] < d { continue; }
        for &(w, v) in &dist[u] {
            if dp[u] + w < dp[v] {
                dp[v] = dp[u] + w;
                pq.push(Node { d: dp[v], u: v });
            }
        }
    }
    let mut ret = 0.;
    for u in 1..=n {
        ret = f64::max(ret, dp[u] / vel[u - 1] as f64);
    }
    println!("{:.1}", ret);
}