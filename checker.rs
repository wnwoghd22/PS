use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        eprintln!("Usage: {} <file1> <file2>", args[0]);
        std::process::exit(1);
    }

    let filename1 = &args[1];
    let filename2 = &args[2];

    let file1 = File::open(filename1)?;
    let file2 = File::open(filename2)?;

    let reader1 = BufReader::new(file1);
    let reader2 = BufReader::new(file2);

    for (index, (line1, line2)) in reader1.lines().zip(reader2.lines()).enumerate() {
        let num1: f64 = line1?.trim().parse().expect("Failed to parse number in file1");
        let num2: f64 = line2?.trim().parse().expect("Failed to parse number in file2");

        if !are_close(num1, num2, 1e-6) {
            println!("Mismatch on line {}: {} != {}", index + 1, num1, num2);
        }
    }

    Ok(())
}

// compare relative values
fn are_close(a: f64, b: f64, tolerance: f64) -> bool {
    if a == b {
        true
    } else {
        let abs_diff = (a - b).abs();
        let max_abs = a.abs().max(b.abs());
        abs_diff / max_abs < tolerance
    }
}
