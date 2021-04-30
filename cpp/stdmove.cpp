// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.
#include <cstdio>
#include <utility>
#include <vector>
struct Complex {
  int real;
  int image;
};
void bar(Complex c) {
  printf("%d+%di\n", c.real, c.image);
}
void foo() {
  Complex c {3, 4};
  bar(std::move(c));
  bar(std::move(c));
}

int main() {
  foo();
  return 0;
}