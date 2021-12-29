//
// Created by Jiang Yinzuo on 2021/12/17.
//

#include <barrier>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main() {
  std::shared_ptr<int> p = std::make_shared<int>(123);
  std::cout << p.use_count() << std::endl;
  std::barrier b{100, [&]() {
                   std::cout << "count: " << p.use_count() << " value: " << *p
                             << std::endl;
                   std::cout << std::atomic_ref(*p).load() << std::endl;
                 }};
  std::vector<std::thread> threads{100};

  std::atomic_int counter{0};
  for (auto &t : threads) {
    t = std::thread{[&]() {
      b.arrive_and_wait();
      std::shared_ptr<int> p2{p};
      if (counter.fetch_add(1, std::memory_order_acq_rel) == 50) {
        std::atomic_ref(*p2).store(50);
      }
      (void)p2;
      b.arrive_and_wait();
    }};
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}
