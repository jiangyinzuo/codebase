/// rustc -O --crate-type=lib --emit asm lib.rs
pub fn foo(s: [i32; 5]) -> i32 {
    let mut sum = 0;
    let iter = s.iter();
    let iter2 = iter.clone();
    for i in iter {
        sum += i;
    }
    for i in iter2 {
        sum *= i;
    }
    sum
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
