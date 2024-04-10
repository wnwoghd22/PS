const DX: [i32; 4] = [1, -1, 0, 0];
const DY: [i32; 4] = [1, -1, 0, 0];
const DELTA: [(i32, i32); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

fn main() {
    let arr: [i32; 5] = [1, 2, 3, 4, 5];
    println!("{}", arr[0]);
    println!("{}, {}", DX[0], DY[0]);
    println!("({}, {})", DELTA[0].0, DELTA[0].1);

    for (dx, dy) in DELTA {
        println!("({}, {})", dx, dy);
    }
}