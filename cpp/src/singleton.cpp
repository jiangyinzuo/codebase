#include <array>
#include <atomic>
#include <barrier>
#include <cassert>
#include <iostream>

class Foo {
 public:
  static Foo& GetSingleton() {
    static Foo foo;
    return foo;
  }

  static std::atomic_int init_count_;

 private:
  Foo() {
    ++init_count_;
    std::cout << "constructor" << std::endl;
  }
};

std::atomic_int Foo::init_count_{0};

int main() {
  std::array<std::thread, 100> arr;
  std::barrier barrier{100};
  for (auto& t : arr) {
    t = std::thread([&barrier]() {
      barrier.arrive_and_wait();
      Foo::GetSingleton();
    });
  }

  for (auto& t : arr) {
    t.join();
  }
  assert(Foo::init_count_.load(std::memory_order_acquire) == 1);
  return 0;
}