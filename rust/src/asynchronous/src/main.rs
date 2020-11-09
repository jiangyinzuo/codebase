use futures::executor::block_on;

async fn foo() {
    println!("foo");
}
fn main() {
    let future = foo();
    println!("Hello, world!");
    block_on(future);
}
