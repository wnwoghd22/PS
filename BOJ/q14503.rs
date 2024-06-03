use std::io;

const DELTA: [(i32, i32); 4] = [(-1, 0), (0, 1), (1, 0), (0, -1)];

fn adjacent(x: usize, y: usize, dx: i32, dy: i32, n: usize, m: usize) -> Option<(usize, usize)> {
    if x == 0 && dx == -1 { return None; }
    if y == 0 && dy == -1 { return None; }
    let x = (x as i32 + dx) as usize;
    let y = (y as i32 + dy) as usize;
    if x < n && y < m {
        Some((x, y))
    } else {
        None
    }
}

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m] = v[..] else { panic!(); };

    let mut ss = String::new();
    io::stdin().read_line(&mut ss).unwrap();
    let v: Vec<usize> = ss
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [r, c, d] = v[..] else { panic!(); };

    let mut x = r;
    let mut y = c;
    let mut dir = d;

    let mut map: Vec<Vec<i32>> = vec![];
    for _ in 0..n {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<i32> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        map.push(v);
    }
    let mut ret = 0;

    loop {
        // 1. clean a grid if the grid is dirty
        if map[x][y] == 0 {
            ret += 1;
            map[x][y] = -1;
        }
        // check adj
        let mut adj = 0;
        for (dx, dy) in DELTA {
            if let Some((nx, ny)) = adjacent(x, y, dx, dy, n, m) {
                if map[nx][ny] == 0 {
                    adj += 1;
                }
            }
        }
        if adj == 0 { // 2
            let rv = (dir + 2) % 4;
            if let Some((nx, ny)) = adjacent(x, y, DELTA[rv].0, DELTA[rv].1, n, m) {
                if map[nx][ny] == 1 {
                    break;
                }
                x = nx;
                y = ny;
            } else {
                break;
            }
        } else { // 3
            dir = (dir + 3) % 4;
            if let Some((nx, ny)) = adjacent(x, y, DELTA[dir].0, DELTA[dir].1, n, m) {
                if map[nx][ny] == 0 {
                    x = nx;
                    y = ny;
                }
            }
        }
    }
    println!("{}", ret);
}