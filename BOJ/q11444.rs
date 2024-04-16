use std::io;

fn main() {
    const DIVISOR:u64=1_000_000_007;
    let fibonacci_matrix = [[1, 1], [1, 0]];
    let mut listing_fibonacci_matrix: Vec<[[u64; 2]; 2]> =Vec::with_capacity(65);
    listing_fibonacci_matrix.push(fibonacci_matrix);

    let multiplication_fib=|a:[[u64;2];2],b:[[u64;2];2]|->[[u64;2];2]{
        let mut result=[[0;2];2];
        for i in 0..2{
            for j in 0..2{
                for k in 0..2{
                    result[i][j]+=(a[i][k]*b[k][j]%DIVISOR);
                    result[i][j]%=DIVISOR;
                }

            }
        }
        result
    };
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("no input");
    let input=s.trim().parse::<u64>().unwrap();
    
    match input {
        0=>{println!("0")},
        _=>{
            let mut counter=0;
            let mut powers:[bool;65]=[false;65];
            while (1<<counter)<=input{
                if (input>>counter)&1==1{powers[counter]=true;}
                counter+=1;
            }
            for i in 1..counter{
                listing_fibonacci_matrix.push(multiplication_fib(listing_fibonacci_matrix[i-1],listing_fibonacci_matrix[i-1]));
            }
            let mut finalt:[[u64;2];2]=[[1,0],[0,1]];
            for i in 0..counter{
                if powers[i]{
                    finalt=multiplication_fib(finalt,listing_fibonacci_matrix[i]);
                }
            }
            println!("{}",finalt[1][0]);
        }
    }
}
