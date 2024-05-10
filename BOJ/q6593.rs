use std::io;
use std::collections::VecDeque;

static DELTA: [(i32, i32, i32); 6] = [(0, 0, 1), (0, 0, -1), (0, 1, 0), (0, -1, 0), (1, 0, 0), (-1, 0, 0)];

struct Map {
    layers: usize,
    rows: usize,
    columns: usize,
    map: Vec<Vec<Vec<bool>>>,
    init_pos: (usize, usize, usize),
    target_pos: (usize, usize, usize),
}

impl Map {
    fn new(size: &Vec<usize>) -> Map {
        let (layers, rows, columns) = (size[0], size[1], size[2]);
        let mut map = vec![vec![vec![true; columns]; rows]; layers];
        let mut init_pos = (0, 0, 0);
        let mut target_pos = (0, 0, 0);
        for l in 0..layers {
            for r in 0..rows {
                let mut s = String::new();
                io::stdin().read_line(&mut s).unwrap();
                let arr: Vec<char> = s.chars().collect();
                for c in 0..columns {
                    if arr[c] == 'S' { init_pos = (l, r, c); }
                    if arr[c] == 'E' { target_pos = (l, r, c); }
                    if arr[c] == '#' {
                        map[l][r][c] = false;
                    }
                }
            }
            let mut s = String::new();
            io::stdin().read_line(&mut s).unwrap();
        }

        Map {
            layers,
            rows,
            columns,
            map,
            init_pos,
            target_pos,
        }
    }

    fn bfs(&self) -> Option<i32> {
        let mut queue: VecDeque<(usize, usize, usize)> = VecDeque::with_capacity(30000);
        let mut visited: Vec<Vec<Vec<i32>>> = vec![vec![vec![-1; self.columns]; self.rows]; self.layers];

        queue.push_back(self.init_pos);
        let (l, r, c) = self.init_pos;
        visited[l][r][c] = 0;

        while let Some((l, r, c)) = queue.pop_front() {
            if (l, r, c) == self.target_pos {
                return Some(visited[l][r][c]);
            }

            for (dx, dy, dz) in DELTA {
                let nl = l as i32 + dx;
                let nr = r as i32 + dy;
                let nc = c as i32 + dz;
                if nl < 0 || nr < 0 || nc < 0 { continue; }
                let nl = nl as usize;
                let nr = nr as usize;
                let nc = nc as usize;
                if nl >= self.layers || nr >= self.rows || nc >= self.columns { continue; }
                if visited[nl][nr][nc] != -1 { continue; }
                if !self.map[nl][nr][nc] { continue; }
                visited[nl][nr][nc] = visited[l][r][c] + 1;
                queue.push_back((nl, nr, nc));
            }
        }

        None
    }
}

fn main() {
    loop {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let size: Vec<usize> = s
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        if size == [0, 0, 0] {
            break;
        }
        let map = Map::new(&size);
        if let Some(t) = map.bfs() {
            println!("Escaped in {} minute(s).", t);
        } else { 
            println!("Trapped!");
        }
    }
}