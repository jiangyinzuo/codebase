fn match_number(x: i32) -> i32 {
    match x {
        e @ 1..=10 => {
            println!("small {}", e);
            1
        }
        _ => 99
    }
}

fn main() {
    let mut s: String = "".to_string();
    std::io::stdin().read_line(&mut s).unwrap();
    match s.as_str() {
        s if s.is_empty() => {
            println!("empty");
        }
        | "hello"
        | "world" => {
            println!("hello");
        }
        _ => {
            println!("foo");
        }
    }

    match_number(1);
}
