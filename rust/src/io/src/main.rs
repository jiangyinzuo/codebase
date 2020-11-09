fn main() {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    let mut s = s.trim().split_whitespace();
    let a: i32 = s.next().unwrap().parse().unwrap();
    let b: i32 = s.next().unwrap().parse().unwrap();
    println!("{}", a + b);
}
