use std::io;

fn main() {
    loop {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        let v: Vec<usize> = s.split_whitespace().map(|x| x.parse().unwrap()).collect();
        if v[0] == 0 && v[1] == 0 && v[2] == 0 {
            break;
        }
        
        let mut sum = 0;
        let mut max = 0;
        for &k in &v {
            sum += k;
            if k > max { max = k; }
        }
        if sum - max <= max {
            println!("Invalid");
        } else if v[0] == v[1] && v[1] == v[2] {
            println!("Equilateral");
        } else if v[0] == v[1] || v[1] == v[2] || v[2] == v[0] {
            println!("Isosceles");
        } else {
            println!("Scalene");
        }
    }
}