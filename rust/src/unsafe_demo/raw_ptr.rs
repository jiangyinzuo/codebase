struct Num(i32);
impl Drop for Num {
    fn drop(&mut self) {
        println!("drop Num({})", self.0);
    }
}
struct Foo(*mut Num);

fn foo(foo: &mut Foo) {
    let mut a = Num(43);
    foo.0 = &mut a;
}

fn bar() -> *mut Num {
    let mut a = Num(433);
    &mut a
}
fn baz() -> *mut i32 {
    let mut a = 324444;
    &mut a
}

#[test]
fn test() {
    let mut f = Foo(std::ptr::null_mut());
    foo(&mut f);
    // unsafe {
    //     *f.0 = 444;
    // };
    let n = unsafe { (*f.0).0 };
    println!("{}", n);
    f.0 = bar();
    let n = unsafe { (*f.0).0 };
    println!("{}", n);
    let mut f2 = Foo(std::ptr::null_mut());
    foo(&mut f2);
    foo(&mut f2);

    println!("{}", n);

    let a = Num(1233);
    let b = &a as *const Num;
    std::mem::drop(a);
    println!("{}", unsafe{(*b).0});
    let bc = baz();
    println!("UB: ");
    let a = Num(1233);
    let b = &a as *const Num;
    std::mem::drop(a);
    println!("{}", unsafe{(*b).0});
    println!("{}", unsafe{*bc});

}
