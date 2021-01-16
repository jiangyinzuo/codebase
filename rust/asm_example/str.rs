fn show(c: char) {
    println!("{}", c);
}

/// rustc -O --emit asm str
fn main() {
    let mut a = "hello".chars();
    for c in a {
        show(c);
    }

}
