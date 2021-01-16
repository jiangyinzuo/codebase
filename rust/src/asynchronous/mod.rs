use futures::executor::block_on;

async fn foo() {
    println!("foo");
}

#[test]
fn foo_test() {
    let future = foo();
    println!("Hello, world!");
    block_on(future);
}
