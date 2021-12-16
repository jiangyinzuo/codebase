//
// Created by Jiang Yinzuo on 2021/12/9.
//

#include <iostream>
#include <map>
template <typename T, typename R>
struct Foo;

template <typename T, typename R>
std::map<int, T> Foo<T, R>::m;

template <typename T, typename R>
struct Foo {
  static std::map<int, T> m;
  void bar();
};
template <typename T, typename R>
void Foo<T, R>::bar() {}

int main() {
  Foo<std::string, void>::m[1] = "foo";
  std::cout << Foo<std::string, void>::m[1] << std::endl;
  return 0;
}