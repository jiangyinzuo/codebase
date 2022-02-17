// 编译参数-O0 和-O2结果不同

#include <iostream>

class Base {
 public:
  virtual ~Base() = default;
  virtual void Foo() {
    std::cout << "Base\n";
  }
};

class Derive : public Base {
 public:
  void Foo() override {
    std::cout << "Derive\n";
  }
};

int main() {
  Derive *d = new Derive();
  d->~Derive();
  d->Foo(); // UB
  d = new (d) Derive(); // UB
  d->Foo(); // UB
  delete d;
  // d->Foo(); // UB
  Derive d2;
  d2.~Derive(); // UB
  d2.Foo();
  return 0;
}