use std::io::{self, BufRead, Write};

fn acosh(x: f64) -> f64 {
    (x + (x * x - 1.0).sqrt()).ln()
}

fn main() {
    let mut iter = io::stdin().lock().lines();
    let mut writer = io::BufWriter::new(io::stdout());
    let tc: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..tc {
        let v: Vec<f64> = iter.next().unwrap().unwrap()
            .split_whitespace().map(|x| x.parse().unwrap()).collect();
        let dx = v[2] - v[0];
        let dy = v[3] - v[1];
        let x = 1.0 + (dx * dx + dy * dy) / (2.0 * v[1] * v[3]);
        _ = writeln!(writer, "{}", acosh(x));
    }
    writer.flush().unwrap();
}