//
// Created by Jiang Yinzuo on 2021/12/17.
//

#include <string>
#include <utility>
template <typename T>
void foo(T &&a) {
  (void)(a);
}
int bar(int a) { return a + 4; }
std::string foo() { return ""; }
std::string g;
std::string &bar() { return g; }
auto foo3() { return foo(); }
auto &&f() {
  int c = 3;
  int &d = c;
  return d;
}
auto bar2() {
  auto b = bar();
  decltype(auto) b2 = bar();
  return bar();
}

int main() {
  int a = 1;
  //  int &b = a;
  //  auto c = std::forward<int&>(4);
  decltype(bar(3)) e = 3;
  (void)e;
  decltype(std::forward<int &>(4)) d = a;
  //  (void)c;
  (void)d;
  //  decltype() d = 4;
  //  (void)d;
  foo(a);
}