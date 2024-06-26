use std::env;
use std::process;

use jay202_minigrep::Config;

fn main() {
    let config = Config::build(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {err}");
        process::exit(0);
    });

    if let Err(e) = jay202_minigrep::run(config) {
        eprintln!("Application error: {e}");
        process::exit(1);
    }
}