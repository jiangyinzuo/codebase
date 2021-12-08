// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

// template<typename T>
// void foo(A<T> a) {}
//
// void bar(int b) {
//   foo(b);
// }

template <typename T> class A {};

template <typename T>
class Foo {
public:
  void foo(A<T> a) {}

  void bar(int a) { this->foo(a); }
};

int main() {
  //  Foo<int> f;
  //  f.bar(3);
  return 0;
}