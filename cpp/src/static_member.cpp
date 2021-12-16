//
// Created by Jiang Yinzuo on 2021/12/14.
//

#include <iostream>

int min(const int &a, const int &b) { return a < b ? a : b; }

class Foo {
 public:
  static const int BAR = 42;
  void F1(int b) { min(Foo::BAR, 4); }
};
// const int Foo::BAR;
void F2(int b) { min(Foo::BAR, 4); }

int main() {
  const int *a [[maybe_unused]] = &Foo::BAR;
  std::cout << Foo::BAR << &Foo::BAR << std::endl;
  return 0;
}