/// rustc -O --crate-type=lib --emit asm map.rs
pub fn map() -> i32 {
    let mut a = 0;
    for i in 1..10 {
        a += i;
    }
    a
}

pub unsafe fn bar() -> i32 {
    let mut a = 0;
    for i in 1..10 {
        a += i;
    }
    a
}