trait Flyable {
    fn fly(&self);
}

struct Dog;
struct Duck;

impl Flyable for Dog {
    fn fly(&self) {
        println!("Dog fly");
    }
}

impl Flyable for Duck {
    fn fly(&self) {
        println!("Duck fly");
    }
}

#[test]
fn demo2_test() {
    let animals: [&dyn Flyable; 2] = [&Dog {}, &Duck {}];
    for animal in animals.iter() {
        animal.fly();
    }
    let animal_vec: Vec<&dyn Flyable> = vec![&Dog {}, &Duck {}];
    for animal in animal_vec {
        animal.fly();
    }
}
