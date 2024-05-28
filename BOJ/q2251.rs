use std::io;
use std::collections::VecDeque;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let v: Vec<usize> = s
        .as_mut_str()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let [a, b, c] = v[..] else { panic!(); };

    let mut visited: Vec<Vec<Vec<bool>>> = vec![vec![vec![false; c + 1]; b + 1]; a + 1];
    let mut q: VecDeque<(usize, usize, usize)> = VecDeque::new();
    visited[0][0][c] = true;
    q.push_back((0, 0, c));

    while let Some((i, j, k)) = q.pop_front() {
        let (ni, nj, nk) = if i + j <= b {
            (0, i + j, k)
        } else {
            (i - (b - j), b, k)
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }

        let (ni, nj, nk) = if i + k <= c {
            (0, j, i + k)
        } else {
            (i - (c - k), j, c)
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }

        let (ni, nj, nk) = if i + j <= a {
            (i + j, 0, k)
        } else {
            (a, j - (a - i), k)
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }

        let (ni, nj, nk) = if j + k <= c {
            (i, 0, j + k)
        } else {
            (i, j - (c - k), c)
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }
        
        let (ni, nj, nk) = if i + k <= a {
            (i + k, j, 0)
        } else {
            (a, j, k - (a - i))
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }

        let (ni, nj, nk) = if j + k <= b {
            (i, j + k, 0)
        } else {
            (i, b, k - (b - j))
        }; 
        if !visited[ni][nj][nk] {
            visited[ni][nj][nk] = true;
            q.push_back((ni, nj, nk));
        }
    }

    let mut ret: Vec<bool> = vec![false; c + 1];
    for i in 0..b + 1 {
        for j in 0..c + 1 {
            if visited[0][i][j] {
                ret[j] = true;
            }
        }
    }
    for i in 0..c + 1 {
        if ret[i] {
            print!("{} ", i);
        }
    }
}