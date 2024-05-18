use std::io::{self, BufRead};
use std::cmp::Ordering;

static DELTA: [(i32, i32); 8] = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)];

fn adjacent(x: usize, y: usize, dx: i32, dy: i32, r: usize, c: usize) -> Option<(usize, usize)> {
    if dx == -1 && x == 0 { return None; }
    if dy == -1 && y == 0 { return None; }
    let nx = (x as i32 + dx) as usize;
    let ny = (y as i32 + dy) as usize;
    if nx >= r || ny >= c { return None; }
    Some((nx, ny))
}

struct Tree {
    age: u32,
    r: usize,
    c: usize,
}

impl PartialEq for Tree {
    fn eq(&self, other: &Self) -> bool {
        self.age == other.age
    }
}

impl Eq for Tree {}

impl PartialOrd for Tree {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for Tree {
    fn cmp(&self, other: &Self) -> Ordering {
        self.age.cmp(&other.age)
    }
}

fn main() {
    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();

    let s = iterator.next().unwrap().unwrap();
    let v: Vec<usize> = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [n, m, k] = v[..] else { panic! (); };
    let mut nutrient: Vec<Vec<u32>> = vec![vec![5; n]; n];

    let mut robot: Vec<Vec<u32>> = Vec::with_capacity(n);
    for _ in 0..n {
        let s = iterator.next().unwrap().unwrap();
        let row: Vec<u32> = s
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        robot.push(row);
    }
    let robot: Vec<Vec<u32>> = robot;

    let mut trees: Vec<Tree> = Vec::new();
    for _ in 0..m {
        let s = iterator.next().unwrap().unwrap();
        let v: Vec<usize> = s
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        trees.push(Tree {
            age: v[2] as u32,
            r: v[0] - 1,
            c: v[1] - 1,
        });
    }

    for _ in 0..k {
        let mut dead: Vec<Tree> = Vec::new();
        let mut mature: Vec<Tree> = Vec::new();
        let mut alive: Vec<Tree> = Vec::new();

        { // spring
            trees.sort();
            for Tree {age, r, c} in &trees {
                let mut age = *age;
                let r = *r;
                let c = *c;
                if nutrient[r][c] < age {
                    dead.push(Tree { age, r, c });
                    continue;
                }
                nutrient[r][c] -= age;
                age += 1;
                if age % 5 == 0 { mature.push(Tree { age, r, c }); }
                alive.push(Tree { age, r, c });
            }
        }

        { // summer
            for Tree {age, r, c} in &dead {
                let nut = age / 2;
                let r = *r;
                let c = *c;
                nutrient[r][c] += nut;
            }
        }

        { // autumn
            for Tree {r, c,..} in &mature {
                for (dx, dy) in DELTA {
                    if let Some((nx, ny)) = adjacent(*r, *c, dx, dy, n, n) {
                        alive.push(Tree {
                            age: 1,
                            r: nx,
                            c: ny,
                        });
                    }
                }
            }
        }

        { // winter
            for r in 0..n {
                for c in 0..n {
                    nutrient[r][c] += robot[r][c];
                }
            }
        }

        trees = alive;
    }
    println!("{}", trees.len());
}