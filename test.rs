use std::fs::File;
use std::error::Error;
use std::io::{self, Read, ErrorKind};

fn read_username_from_file() -> Result<String, io::Error> {
    let mut username = String::new();
    File::open("hello.txt")?.read_to_string(&mut username)?;
    Ok(username)
}

fn main() -> Result<(), Box<dyn Error>> {
    let greeting_file_result = File::open("hello.txt")?;

    let username = read_username_from_file().unwrap();

    Ok(())
}