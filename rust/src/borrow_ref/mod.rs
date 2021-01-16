mod problem1;

use crate::borrow_ref::Token::Name;

struct Student<'a> {
    age: u32,
    name: &'a str,
}

impl<'a> Student<'a> {
    fn get_name(&mut self) -> Token<'a> {
        self.age += 1;
        // self.name = &self.name[1..];
        Name(&self.name[1..2])
    }
}

enum Token<'a> {
    Name(&'a str),
}

#[test]
fn student_test() {
    let mut s = Student {
        age: 3,
        name: "alice",
    };
    s.age += 1;
    s.age += 1;
    let mut vec = vec![];
    let c = s.get_name();
    vec.push(c);
    let d = s.get_name();
    vec.push(d);
    assert_eq!(vec.len(), 2);
}
