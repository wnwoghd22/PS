use std::{io, collections::HashMap};

fn main() {
    let mut s = String::new();

    io::stdin().read_line(&mut s).unwrap();

    let values:Vec<i32> = s
        .as_mut_str()
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let n = values[0];
    let k = values[1];

    let mut t = String::new();

    io::stdin().read_line(&mut t).unwrap();

    let arr:Vec<i32> = t
        .as_mut_str()
        .split_whitespace()
        .map(|t| t.parse().unwrap())
        .collect();

    let mut sums: Vec<i32> = vec![0];
    for a in arr {
        sums.push(sums[sums.len() - 1] + a);
    }

    let mut counts: HashMap<i32, u64> = HashMap::new();
    let mut result: u64 = 0;
    for sum in sums {
        if let Some(x) = counts.get(&(sum - k)) { result += x; }
        let count = counts.entry(sum).or_insert(0);
        *count += 1;
    }
    println!("{}", result);
}