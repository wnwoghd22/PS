struct CustomSmartPointer {
    data: String,
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Drop {}", self.data);
    }
}

fn main() {
    let c = CustomSmartPointer {
        data: String::from("fuck")
    };

    let d = CustomSmartPointer {
        data: String::from("you")
    };
    println!("pointers created");
    drop(c);
}
