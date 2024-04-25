use std::io;

fn main() {
    let mut cnts = vec![0; 6];
    for i in 0..6 {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        cnts[i] = s.trim().parse().unwrap();
    }
    let mut cnt = 0;

    // 6 * 6
    cnt += cnts[5];

    // 5 * 5
    cnt += cnts[4];
    cnts[0] -= cnts[4] * 11;

    // 4 * 4
    cnt += cnts[3];
    cnts[1] -= cnts[3] * 5;
    if cnts[1] < 0 {
        cnts[0] += cnts[1] * 4;
        cnts[1] = 0;
    }

    // 3 * 3
    cnt += cnts[2] / 4;
    cnts[2] %= 4;
    if cnts[2] != 0 { cnt += 1; }
    match cnts[2] {
        1 => {
            cnts[1] -= 5;
            cnts[0] -= 7;
            
        },
        2 => {
            cnts[1] -= 3;
            cnts[0] -= 6;
        },
        3 => {
            cnts[1] -= 1;
            cnts[0] -= 5;
        },
        _ => ()
    }
    if cnts[1] < 0 {
        cnts[0] += cnts[1] * 4;
        cnts[1] = 0;
    }

    // 2 * 2
    cnt += cnts[1] / 9;
    cnts[1] %= 9;
    if cnts[1] != 0 { 
        cnt += 1;
        cnts[0] -= 36 - cnts[1] * 4;
    }

    // 1 * 1
    if cnts[0] > 0 { 
        cnt += cnts[0] / 36;
        cnts[0] %= 36;
        if cnts[0] != 0 { cnt += 1; }
    }

    println!("{}", cnt);
}