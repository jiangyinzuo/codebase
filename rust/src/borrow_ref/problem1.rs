//! #Reference:
//! https://stackoverflow.com/questions/58295535/cannot-borrow-self-as-mutable-more-than-once-at-a-time-when-returning-a-resul

struct Foo<'a>(&'a str);

impl<'a: 'b, 'b> Foo<'a> {
    fn mutable1(&'b mut self) -> &'a str {
        &self.0[1..2]
    }
}

#[test]
fn test() {
    let mut f = Foo("hello");
    let res1 = f.mutable1();
    let res2 = f.mutable1();
    assert_eq!(res1, res2);
}
