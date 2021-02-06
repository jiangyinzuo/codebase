use std::ops::Deref;
use std::rc::Rc;

#[derive(Debug, PartialEq)]
enum Color {
    Red,
    Yellow,
    Green,
}

/// Rc<T> 引用计数大于1时，不能改变值
struct Pane {
    color: Rc<Color>,
}
struct Text {
    color: Rc<Color>,
}

#[test]
fn test() {
    let color = Rc::new(Color::Red);
    let mut pane = Pane {
        color: Rc::clone(&color),
    };
    
    assert_eq!(Color::Red, *pane.color.deref());
    std::mem::drop(color);
    
    // Returns a mutable reference into the given `Rc`, if there are
    // no other `Rc` or [`Weak`] pointers to the same allocation.
    //
    // Returns [`None`] otherwise, because it is not safe to
    // mutate a shared value.
    let c = Rc::get_mut(&mut pane.color).unwrap();
    *c = Color::Yellow;

    assert_eq!(Color::Yellow, *pane.color.deref());
    let text = Text {
        color: Rc::clone(&pane.color),
    };
    assert_eq!(Rc::strong_count(&text.color), 2);
}
