use std::io::{self, BufRead, Write};

#[derive(Debug, Clone, Copy)]
struct Pos {
    x: i64,
    y: i64,
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

fn conquer(l: usize, m: usize, r: usize, arr: &mut Vec<Pos>, tmp: &mut Vec<Pos>, pvt: &Pos) -> i64 {
    let mut i = l;
    let mut j = m + 1;
    let mut t = l;
    let mut count = 0;
    while i <= m && j <= r {
        if cross(pvt, &arr[i], &arr[j]) > 0 {
            tmp[t] = arr[i]; 
            t += 1; i += 1;
        }
        else {
            tmp[t] = arr[j];
            t += 1; j += 1;
            count += m - i + 1;
        }
    }
    while i <= m { tmp[t] = arr[i]; t += 1; i += 1; }
    while j <= r { tmp[t] = arr[j]; t += 1; j += 1; }
    i = l;
    while i <= r { arr[i] = tmp[i]; i += 1; }
    count as i64
}

fn divide(l: usize, r: usize, arr: &mut Vec<Pos>, tmp: &mut Vec<Pos>, pvt: &Pos) -> i64 {
    let mut ret = 0;
    if l < r {
        let m = l + r >> 1;
        ret += divide(l, m, arr, tmp, pvt);
        ret += divide(m + 1, r, arr, tmp, pvt);
        ret += conquer(l, m, r, arr, tmp, pvt);
    }
    ret
}

fn merge_sort(arr: &mut Vec<Pos>, tmp: &mut Vec<Pos>, pvt: &Pos) -> i64 {
    divide(0, arr.len() - 1, arr, tmp, pvt)
}

fn query(p1: &Pos, p2: &Pos, p3: &Pos, p4: &Pos, ant: &mut Vec<Pos>) -> i64 {
    let mut tmp: Vec<Pos> = vec![Pos { x: 0, y: 0 }; ant.len()];
    merge_sort(ant, &mut tmp, p2);
    let x = merge_sort(ant, &mut tmp, p3);

    let mut fuck: Vec<Pos> = vec![];
    for &mut p in &mut *ant {
        if ccw(p2, p4, &p) < 0 {
            fuck.push(p);
        }
    }
    let y = if fuck.len() > 0 {
        merge_sort(&mut fuck, &mut tmp, p2);
        merge_sort(&mut fuck, &mut tmp, p4)
    } else { 0 };

    let mut suck: Vec<Pos> = vec![];
    for &mut p in &mut *ant {
        if ccw(p1, p3, &p) < 0 {
            suck.push(p);
        }
    }
    let z = if suck.len() > 0 {
        merge_sort(&mut suck, &mut tmp, p1);
        merge_sort(&mut suck, &mut tmp, p3)
    } else { 0 };

    let cmb1 = ant.len() as i64 * (ant.len() as i64 - 1) / 2;
    let cmb2 = fuck.len() as i64 * (fuck.len() as i64 - 1) / 2;
    let cmb3 = suck.len() as i64 * (suck.len() as i64 - 1) / 2;

    cmb1- x + y - cmb2 + z - cmb3
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let z: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..z {
        iter.next(); // empty line

        let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut hull: Vec<Pos> = vec![];
        for _ in 0..n {
            let v: Vec<i64> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            hull.push(Pos { x: v[0], y: v[1]});
        }

        let m: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        let mut ant: Vec<Pos> = vec![];
        for _ in 0..m {
            let v: Vec<i64> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            ant.push(Pos { x: v[0], y: v[1]});
        }
        
        let q: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        for _ in 0..q {
            let v: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();

            let mut x: Vec<Pos> = vec![];
            let p1 = &hull[v[0]];
            let p2 = &hull[(v[0] + 1) % n];
            let p3 = &hull[v[1]];
            let p4 = &hull[(v[1] + 1) % n];
            for p in &ant {
                if ccw(p1, p4, p) > 0 && ccw(p2, p3, p) < 0 {
                    x.push(*p);
                }
            }
            _ = write!(writer, "{} ", if x.len() > 0 {
                query(p1, p2, p3, p4, &mut x)
            } else { 0 });
        }
        _ = writeln!(writer); 
    }
    writer.flush().unwrap();
}