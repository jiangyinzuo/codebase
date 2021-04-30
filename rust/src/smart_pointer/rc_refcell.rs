use std::rc::Rc;
use std::cell::RefCell;
use std::ops::Deref;

#[derive(Debug, PartialEq)]
enum Color {
    Red,
    Yellow,
    Green,
}

/// Rc<T> 引用计数大于1时，不能改变值
struct Pane {
    color: Rc<RefCell<Color>>,
}

struct Text {
    color: Rc<RefCell<Color>>,
}

#[test]
fn test() {
    let color = Rc::new(RefCell::new(Color::Red));
    let pane = Pane {
        color: Rc::clone(&color)
    };
    let text = Text {
        color: Rc::clone(&color)
    };
    color.replace(Color::Green);
    std::mem::drop(color);
    assert_eq!(2, std::rc::Rc::strong_count(&pane.color));
    assert_eq!(text.color.deref().borrow().deref(), &Color::Green);
    assert_eq!(text.color.deref().borrow().deref(), &Color::Green);
}
