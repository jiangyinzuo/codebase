use proc_macro2::TokenStream;
use quote::*;

#[test]
fn token_test() {
    let foo = "alice";
    let ident_name = format_ident!("hello_{}", foo);
    let tokens = quote! {
        fn #ident_name(a: i32, b: i32) -> i32 {
            a + b * 2
        }
    };

    let token_tree = vec![
        "fn",
        "hello_alice",
        "(a : i32 , b : i32)",
        "-",
        ">",
        "i32",
        "{ a + b * 2 }",
    ];
    for (i, j) in tokens.into_iter().zip(token_tree) {
        assert_eq!(i.to_string(), j);
    }
}

#[test]
fn multiple_test() {
    let k = vec!["a", "b", "c"];
    let v = vec![1, 2, 3];
    let tokens = quote!(
        #( #k => println!("{}", #v), )*
    );
    println!("{}", tokens);
}
