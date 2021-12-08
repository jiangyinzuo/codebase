// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#include <atomic>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

class Buffer {
 public:
  explicit Buffer(size_t n) : buf(new char[n]), n(n) {
    std::cout << "constructor" << std::endl;
  }
  Buffer(const Buffer& buffer) : buf(new char[buffer.n]) {
    std::cout << "copy constructor" << std::endl;
    used = buffer.used.load(std::memory_order_acquire);
    n = buffer.n;

    memcpy(buf, buffer.buf, n);
  }

  Buffer(Buffer&& buffer) noexcept : n(buffer.n) {
    std::cout << "move constructor" << std::endl;
    used = buffer.used.load(std::memory_order_acquire);
    buf = buffer.buf;
    buffer.buf = nullptr;  // avoid double free
  }

  Buffer& operator=(Buffer&) = delete;

  ~Buffer() {
    std::cout << "free" << std::endl;
    delete[] buf;
  }

  char* GetBuf() const { return buf; }

 private:
  std::atomic<int> used;
  char* buf;
  size_t n;
};

class Allocator {
 public:
  explicit Allocator(Buffer& buffer) : buffer_(buffer) {
    std::cout << "construct Allocator by &" << std::endl;
  }

  explicit Allocator(Buffer&& buffer) : buffer_(std::move(buffer)) {
    std::cout << "construct Allocator by &&" << std::endl;
  }

  Buffer& GetBuffer() { return buffer_; }

 private:
  Buffer buffer_;
};

int main() {
  std::string s1{"hello"};
  std::string s2{std::move(s1)};
  std::cout << s1.size() << std::endl;
  std::cout << s2.size() << std::endl;

  Buffer buf(100);
  buf.GetBuf()[2] = 'c';
  //  Buffer buf2 = buf;
  Allocator allocator(std::move(buf));
  //  buf.buf[0] = 'a'; // SIGSEGV
  std::cout << allocator.GetBuffer().GetBuf()[2] << std::endl;
  Buffer& alloc_buf = allocator.GetBuffer();
  alloc_buf.GetBuf()[2] = 'd';
  Buffer b(1);
  return 0;
}