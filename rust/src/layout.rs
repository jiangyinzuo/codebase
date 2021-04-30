use std::alloc::Layout;


struct Foo {
    a: u16,
    b: u32,
    c: u8,
    d: u16
}

#[test]
 fn test() {
    println!("{:?}", Layout::new::<Foo>());
    println!("{:?}", Layout::new::<i8>());

}
