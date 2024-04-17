mod lib;

use lib::{Summary, Tweet};

fn largest<T: PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item
        }
    }
    largest
}

enum HttpState {
    NotFound {
        
    },
    Ok,
}

pub fn notify(item: &impl Summary) {
    println!("notify: {}", item.summarize());
}

fn main() {
    let tweet = Tweet {
        username: String::from("anonymous"),
        content: String::from("hello world"),
        reply: false,
        retweet: false,
    };
    // println!("tweet: {}", tweet.summarize());
    notify(&tweet);

    let number_list = vec![33, 24, 50, 100, 80];

    let result = largest(&number_list);
    println!("largest: {}", result);

    let number_list = vec!['y', 'm', 'c', 'a'];

    let result = largest(&number_list);
    println!("largest: {}", result);
}