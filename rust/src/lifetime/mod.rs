use crate::lifetime::Color::*;

#[derive(Debug)]
enum Color<'a> {
    Red(&'a str),
}

fn foo(text: &str) -> Vec<Color> {
    let mut res = vec![];
    res.push(Red(text.get(0..2).unwrap()));
    res.push(Red(text.get(0..2).unwrap()));
    res
}

#[test]
fn test() {
    let res = foo("hello");
    println!("{:?}", res);
}
