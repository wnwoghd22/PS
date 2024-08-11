use std::io::{self, BufRead};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut arr: Vec<Vec<char>> = vec![];

    for _ in 0..v[0] {
        let v: Vec<char> = iter.next().unwrap().unwrap().chars().collect();
        arr.push(v);
    }

    let mut cnt = 0;
    for i in 0..v[0]-1 {
        let mut b = false;
        for j in 0..v[1]-1 {
            if b {
                b = false; continue;
            } else {
                if arr[i][j] == 'X' && arr[i][j + 1] == 'X' && arr[i + 1][j] == '.' && arr[i + 1][j + 1] == '.' {
                    cnt += 1;
                    b = true;
                }
            }
        }
        b = false;
        for j in 0..v[1]-1 {
            if b {
                b = false; continue;
            } else {
                if arr[i][j] == '.' && arr[i][j + 1] == '.' && arr[i + 1][j] == 'X' && arr[i + 1][j + 1] == 'X' {
                    cnt += 1;
                    b = true;
                }
            }
        }
    }

    for j in 0..v[1]-1 {
        let mut b = false;
        for i in 0..v[0]-1 {
            if b {
                b = false; continue;
            } else {
                if arr[i][j] == 'X' && arr[i + 1][j] == 'X' && arr[i][j + 1] == '.' && arr[i + 1][j + 1] == '.' {
                    cnt += 1;
                    b = true;
                }
            }
        }
        b = false;
        for i in 0..v[0]-1 {
            if b {
                b = false; continue;
            } else {
                if arr[i][j] == '.' && arr[i + 1][j] == '.' && arr[i][j + 1] == 'X' && arr[i + 1][j + 1] == 'X' {
                    cnt += 1;
                    b = true;
                }
            }
        }
    }
    println!("{}", cnt);
}