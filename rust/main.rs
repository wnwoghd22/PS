#[derive(Debug)]
enum List {
    Cons(i32, RefCell<Rc<List>>),
    Nil,
}

impl List {
    fn tail(&self) -> Option<&RefCell<Rc<List>>> {
        match self {
            Cons(_, item) => Some(item),
            Nil => None,
        }
    }
}

use crate::List::{Cons, Nil};
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, RefCell::new(Rc::new(Nil))));
    println!("count: {}", Rc::strong_count(&a));
    println!("next: {:?}", a.tail());

    let b = Rc::new(Cons(10, RefCell::new(Rc::clone(&a))));
    println!("a count: {}", Rc::strong_count(&a));
    println!("b count: {}", Rc::strong_count(&b));
    println!("{:?}", b.tail());

    if let Some(link) = a.tail() {
        *link.borrow_mut() = Rc::clone(&b);
    }
    
    println!("a count: {}", Rc::strong_count(&a));
    println!("b count: {}", Rc::strong_count(&b));

    // println!("next: {:?}", a.tail());
}
