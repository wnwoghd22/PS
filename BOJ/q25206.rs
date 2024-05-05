use std::io;

fn main() {
    let mut num: f64 = 0.0;
    let mut den: f64 = 0.0;
    for _ in 0..20 {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let arr: Vec<String> = s
            .as_mut_str()
            .split_whitespace()
            .map(str::to_string)
            .collect();
        if arr[2] == "P" {
            continue;
        }
        let score = match arr[2].as_str() {
            "A+" => 4.5, "A0" => 4.0,
            "B+" => 3.5, "B0" => 3.0,
            "C+" => 2.5, "C0" => 2.0,
            "D+" => 1.5, "D0" => 1.0,
            "F" => 0.0,
            _ => 0.0,
        };
        let weight = arr[1].trim().parse::<f64>().unwrap();

        num += score * weight;
        den += weight;
    }
    println!("{}", num / den);
}