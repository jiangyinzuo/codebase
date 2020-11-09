trait Say {
    fn say(&self) {
        println!("say");
    }
}

trait Say2 {
    fn say(&self) {
        println!("say2");
    }
}

trait SayHello: Say {
    fn say_hello(&self);
}

struct Person {}

impl Say for Person {}

impl Say2 for Person {
    fn say(&self) {
        println!("say2!!")
    }
}

impl SayHello for Person {
    fn say_hello(&self) {
        println!("hello");
    }
}

#[cfg(test)]
mod tests {
    use crate::trait_demo::*;

    #[test]
    fn hello() {
        let p1 = Person{};
        let p: &dyn Say2 = &p1;
        p.say();
        let p: &dyn Say = &p1;
        p.say();
    }
}
