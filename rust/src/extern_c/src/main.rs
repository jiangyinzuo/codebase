extern "C" {
    fn scanf(format: *const u8, ...) -> i32;
    fn printf(format: *const u8, ...) -> i32;
}

pub fn naive_bytes_iter(s: &str) -> u64 {
    s.bytes().fold(0, |a, c| a * 10 + (c - b'0') as u64)
}

use std::io::stdin;
fn main() {
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).unwrap();
    println!("{}", naive_bytes_iter(buffer.as_str().trim()));
    unsafe {
        let mut a = 0;
        scanf("%d\0".as_ptr(), &mut a);
        printf("hello C %d\n\0".as_ptr(), a);
    }
}
