use std::io::{self, BufRead};
use std::collections::HashMap;
use std::cmp::max;

const SEED: i64 = 5381;
const MOD: i64 = 998_244_353;

fn main() {
    let mut iter = io::stdin().lock().lines();
    let n: usize = iter.next().unwrap().unwrap().trim().parse().unwrap();

    let mut ret = 0;
    let mut map: HashMap<i64, u32> = HashMap::new();
    for _ in 0..n {
        let s: Vec<u8> = iter.next().unwrap().unwrap().trim().as_bytes().to_vec();
        let mut fail: Vec<usize> = vec![0; s.len()];
        let mut hash: Vec<i64> = vec![0; s.len() + 1];
        hash[1] = s[0] as i64;
        let mut j = 0;
        for i in 1..s.len() {
            hash[i + 1] = (hash[i] * SEED + s[i] as i64) % MOD;
            while j > 0 && s[i] != s[j] {
                j = fail[j - 1];
            }
            if s[i] == s[j] {
                j += 1;
                fail[i] = j;
            }
        }
        j = s.len();
        let mut cur = 1;
        while j > 0 {
            if let Some(cnt) = map.get(&hash[j]) {
                cur = max(cur, *cnt + 1);
            }
            j = fail[j - 1];
        }
        ret = max(ret, cur);
        map.insert(hash[s.len()], cur);
    }
    println!("{}", ret);
}