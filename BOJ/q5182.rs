use std::io::{self, BufRead, Write};
use std::cmp::max;

const SCORE: [i32; 10] = [40, 37, 33, 30, 27, 23, 20, 17, 13, 10];

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = std::io::BufWriter::new(std::io::stdout());
    let tc: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();

    for t in 1..tc+1 {
        _ = writeln!(writer, "Data Set {}:", t);
        
        let v: Vec<usize> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let n = v[0];
        let h = v[1];

        let mut dp = vec![0; h+1];
        for _ in 0..n {
            let w: Vec<usize> = iter.next().unwrap().unwrap()
                .split_whitespace().map(|x| x.parse().unwrap()).collect();
            let mut cur = dp.clone();
            for i in 0..10 {
                for j in w[i]..h+1 {
                    cur[j] = max(cur[j], dp[j - w[i]] + SCORE[i]);
                }
            }        
            dp = cur;
            println!("{:?}", dp);
        }
    
        _ = writeln!(writer, "{:.2}", (dp[h] as f64) / n as f64 / 10.);
    }

    writer.flush().unwrap();
}