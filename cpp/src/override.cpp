#include <iostream>
#include <array>

class Base {
 public:
  virtual ~Base() = default;
  virtual void F1(const int a) {
    std::cout << "Base::F1 " << a << std::endl;
  }
};

class Derive : public Base {
 public:
  void F1(int a) override {
    std::cout << "Derive::F1 " << a << std::endl;
  }
};

int main() {
  Derive d;
  d.F1(1);
  std::array<Derive, 1> arr;
  arr[0].F1(2);
  return 0;
}