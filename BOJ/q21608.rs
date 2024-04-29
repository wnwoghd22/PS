use std::io;

static DELTA: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];
static SATISFACTION: [u32; 5] = [0, 1, 10, 100, 1000];

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let n: usize = s.trim().parse().unwrap();

    let mut map: Vec<Vec<u32>> = vec![vec![0; n]; n];
    let mut infos: Vec<Vec<u32>> = Vec::new();
    let mut order: Vec<usize> = vec![0; n * n + 1];

    for i in 0..n * n { 
        let mut x = String::new();
        io::stdin().read_line(&mut x).unwrap();
        let info: Vec<u32> = x
            .as_mut_str()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        order[info[0] as usize] = i;
        infos.push(info);
    }
    for info in &infos {
        let mut max_emp = -1;
        let mut max_sat = -1;
        let mut r = 0;
        let mut c = 0;
        for x in 0..n {
            for y in 0..n {
                if map[x][y] != 0 {
                    continue;
                }

                let mut cur_emp = 0;
                let mut cur_sat = 0;
                for (dx, dy) in DELTA {
                    let nx = x as i32 + dx;
                    let ny = y as i32 + dy;
                    if nx < 0 || ny < 0 {
                        continue;
                    }
                    let nx = nx as usize;
                    let ny = ny as usize;
                    if nx >= n || ny >= n {
                        continue;
                    }
                    if map[nx][ny] == 0 {
                        cur_emp += 1;
                    } else {
                        for &k in &info[1..] {
                            if map[nx][ny] == k {
                                cur_sat += 1;
                                break;
                            }
                        }
                    }
                }
                if cur_sat > max_sat || cur_sat == max_sat && cur_emp > max_emp {
                    r = x;
                    c = y;
                    max_sat = cur_sat;
                    max_emp = cur_emp;
                }
            }
        }
        map[r][c] = info[0];
    }
    let mut ret = 0;
    for x in 0..n {
        for y in 0..n {
            let cur = map[x][y] as usize; 
            let mut sat = 0;
            for (dx, dy) in DELTA {
                let nx = x as i32 + dx;
                let ny = y as i32 + dy;
                if nx < 0 || ny < 0 {
                    continue;
                }
                let nx = nx as usize;
                let ny = ny as usize;
                if nx >= n || ny >= n {
                    continue;
                }
                for &k in &infos[order[cur]][1..] {
                    if map[nx][ny] == k {
                        sat += 1;
                        break;
                    }
                }
            }
            ret += SATISFACTION[sat];
        }
    }

    println!("{}", ret);
}