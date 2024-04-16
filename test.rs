const DX: [i32; 4] = [1, -1, 0, 0];
const DY: [i32; 4] = [1, -1, 0, 0];
const DELTA: [(i32, i32); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

#[derive(Debug)]
struct Pos {
    x: i64,
    y: i64,
}

impl Pos {
    fn magnitude(&self) -> i64 { self.x * self.x + self.y * self.y }
}

enum IpAddrKind {
    v4,
    v6,
}

fn take_ownership(some_str: String) {
    println!("{}", some_str);
}

fn just_get_ref(some_str: &String) {
    println!("{}", some_str);
}


fn main() {
    let some_str = String::from("hello world!");
    // take_ownership(some_str);
    just_get_ref(&some_str);
    println!("{}", some_str);

    let arr: [i32; 5] = [1, 2, 3, 4, 5];
   
    let zero = Pos {
        x: 0,
        y: 0,
    };

    println!("{:?}", zero);

    let p1 = Pos {
        x: 3,
        y: 4,
    };
    println!("{}", p1.magnitude());
}