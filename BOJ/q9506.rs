use std::io;

const LEN: usize = 100_001;

fn main() {
    let mut sum: Vec<usize> = vec![0; LEN];
    let mut arr: Vec<Vec<usize>> = vec![vec![]; LEN];
    for i in 1..LEN {
        for j in (i * 2..LEN).step_by(i) {
            sum[j] += i;
            arr[j].push(i);
        }
    }

    loop {
        let mut s = String::new();
        io::stdin().read_line(&mut s).expect("no input");
        let n: i32 = s.trim().parse().expect("not a number");
        
        if n == -1 { break; }
        let x = n as usize;
        
        if sum[x] == x {
            println!("{} = {}",
                x,
                arr[x]
                .iter()
                .map(|i| i.to_string())
                .collect::<Vec<String>>()
                .join(" + ")
            );
        }
        else {
            println!("{x} is NOT perfect.");
        }
    }
}