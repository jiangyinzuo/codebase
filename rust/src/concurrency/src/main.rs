use std::thread;
use std::sync::mpsc;
use std::sync::mpsc::channel;

fn main() {
    let (tx1, rx1) = channel::<i32>();
    let (tx2, rx2) = channel::<i32>();
    let handle1 = thread::spawn(move || {
        let mut i = 0;
        loop {
            println!("1 : {}", i);
            tx1.send(i + 1).unwrap();
            i = match rx2.recv() {
                Ok(n) if n <= 20 => n,
                _ => return
            };
        }
    });

    let handle2 = thread::spawn(move || {
        let mut i = 0;
        loop {
            i = match rx1.recv() {
                Ok(n) if n <= 20 => n,
                _ => return
            };
            println!(" 2: {}", i);
            tx2.send(i + 1).unwrap();
        }
    });
    handle1.join();
    handle2.join();
}
