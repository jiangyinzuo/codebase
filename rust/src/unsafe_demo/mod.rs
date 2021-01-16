use std::ptr::null;

unsafe fn main() {
    let s = "hello".as_ptr();
    let p: *const i32 = null();
    println!("Hello, world!");
}

#[test]
fn test() {
    unsafe {
        main();
    }
}
