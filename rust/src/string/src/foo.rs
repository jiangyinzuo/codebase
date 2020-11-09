pub fn show(c: char) {
    println!("{}", c);
}

/// rustc -O --crate-type=lib --emit asm foo.rs
pub fn bar() {
    let mut a = "hello".chars();
    for c in a {
        show(c);
    }
}
