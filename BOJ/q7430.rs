use std::io;

static INF: f64 = 1e9;

#[derive(PartialEq, Eq, PartialOrd, Ord, Clone)]
struct Pos {
    x: i64,
    y: i64,
}

fn distance(p1: &Pos, p2: &Pos) -> i64 {
    (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)
}

fn ccw(p1: &Pos, p2: &Pos, p3: &Pos) -> i64 {
   (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
}

fn is_valid_edge(p1: &Pos, p2: &Pos, arr: &Vec<Pos>) -> bool {
    for p in arr {
        if ccw(p1, p2, p) >= 0 {
            return false;
        }
    }

    return true;
}

fn floyd_warshall(n: usize, edges: &Vec<Vec<f64>>) -> Vec<Vec<f64>> {
    let mut dist = vec![vec![INF; n]; n];
    for i in 0..n {
        for j in 0..n {
            if i == j { dist[i][j] = 0.0; }
            else { dist[i][j] = edges[i][j]; }
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

    return dist;
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
    
    let mut ret = INF;
    if m == 0 {
        for i in 0..n {
            for j in 0..n {
                for k in 0..n {
                    if ccw(&towers[i], &towers[j], &towers[k]) != 0 {
                        let d1 = (distance(&towers[i], &towers[j]) as f64).sqrt();
                        let d2 = (distance(&towers[j], &towers[k]) as f64).sqrt();
                        let d3 = (distance(&towers[k], &towers[i]) as f64).sqrt();
                        if d1 + d2 + d3 < ret {
                            ret = d1 + d2 + d3;
                        }
                    }
                }
            }
        }
    }
    else {
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
    
        let mut edges = vec![vec![INF; n]; n];
    
        for i in 0..n {
            let mut j = (i + 1) % n;
            while j != i {
                if is_valid_edge(&towers[i], &towers[j], &monuments) {
                    edges[i][j] = (distance(&towers[i], &towers[j]) as f64).sqrt();
                }
                else { break; }
    
                j = (j + 1) % n;
            }
        }
        
        let dist = floyd_warshall(n, &edges);
        
        for i in 0..n {
            for j in 0..n {
                if i == j { continue; }
                let d = dist[i][j] + dist[j][i];
                if d < ret { ret = d; }
            }
        }
    }
    println!("{:.2}", ret);
}