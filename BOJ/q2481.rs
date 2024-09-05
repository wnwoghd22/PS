use std::io::{self, BufRead, Write};
use std::collections::{VecDeque, HashMap};

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let v: Vec<usize> = iter.next().unwrap().unwrap()
        .split_whitespace().map(|x| x.parse().unwrap()).collect();
    let (n, k) = (v[0], v[1]);
    let mut map: HashMap<i32, usize> = HashMap::new();
    let mut code: Vec<i32> = vec![0; n + 1];
    for i in 1..=n {
        let next = iter.next().unwrap().unwrap();
        match i32::from_str_radix(&next, 2) {
            Ok(number) => { 
                map.insert(number, i);
                code[i] = number;
            }
            Err(_) => panic!("Not a binary!"),
        };
    }
    let mut q: VecDeque<usize> = VecDeque::new();
    let mut d: Vec<i32> = vec![-1; n + 1];
    q.push_back(1);
    d[1] = 0;
    while let Some(u) = q.pop_front() {
        for b in 0..k {
            if let Some(&v) = map.get(&(code[u] ^ 1 << b)) {
                if d[v] != -1 { continue; }
                d[v] = d[u] + 1;
                q.push_back(v);
            }
        }
    }

    let m: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    'query:
    for _ in 0..m {
        let mut u: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
        if d[u] == -1 {
            _ = writeln!(writer, "-1");
            continue 'query;
        }
        let mut path: Vec<usize> = vec![];
        'tracing:
        while u != 1 {
            path.push(u);
            for b in 0..k {
                if let Some(&v) = map.get(&(code[u] ^ 1 << b)) {
                    if d[v] == d[u] - 1 { 
                        u = v;
                        continue 'tracing; 
                    }
                }
            }
        }
        path.push(1);
        for x in path.iter().rev() {
            _ = write!(writer, "{} ", x);
        }
        _ = writeln!(writer);
    }
}