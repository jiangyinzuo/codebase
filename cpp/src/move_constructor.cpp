// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#include <atomic>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

class Buffer {
 public:
  explicit Buffer(size_t n) : id_(next_id++), buf(new char[n]), n(n) {
    std::cout << "constructor " << id_ << std::endl;
  }
  Buffer(const Buffer& buffer) : id_(next_id++), buf(new char[buffer.n]) {
    std::cout << "copy constructor" << id_ << std::endl;
    used = buffer.used.load(std::memory_order_acquire);
    n = buffer.n;

    memcpy(buf, buffer.buf, n);
  }

  Buffer(Buffer&& buffer) noexcept : id_(next_id++), n(buffer.n) {
    std::cout << "move constructor " << id_ << std::endl;
    used = buffer.used.load(std::memory_order_acquire);
    buf = buffer.buf;
    buffer.buf = nullptr;  // avoid double free
  }

  Buffer& operator=(Buffer&) = delete;

  ~Buffer() {
    std::cout << "free " << id_ << ": ";
    if (buf == nullptr) {
      std::cout << "null" << std::endl;
    } else {
      std::cout << (void*)buf << std::endl;
    }
    delete[] buf;
  }

  char* GetBuf() const { return buf; }
  int GetID() const { return id_; }

 private:
  static int next_id;
  int id_;
  std::atomic<int> used;
  char* buf;
  size_t n;
};

int Buffer::next_id = 0;

class Allocator {
 public:
  explicit Allocator(Buffer& buffer) : buffer_(buffer) {
    std::cout << "construct Allocator by &, buffer_id: " << buffer_.GetID() << std::endl;
  }

  explicit Allocator(Buffer&& buffer) : buffer_(std::move(buffer)) {
    std::cout << "construct Allocator by &&, buffer_id: " << buffer_.GetID()
              << std::endl;
  }

  Buffer& GetBuffer() { return buffer_; }

 private:
  Buffer buffer_;
};

void test_move() {
  std::cout << "-------------test_move-----------" << std::endl;
  Buffer buf(100);
  buf.GetBuf()[2] = 'c';
  //  Buffer buf2 = buf;
  Allocator allocator(std::move(buf));
  //  buf.buf[0] = 'a'; // SIGSEGV
  std::cout << allocator.GetBuffer().GetBuf()[2] << std::endl;
  Buffer& alloc_buf = allocator.GetBuffer();
  alloc_buf.GetBuf()[2] = 'd';
}

void test_rvalue() {
  std::cout << "------------test_rvalue-----------" << std::endl;
  Allocator allocator2(Buffer(2));
  allocator2.GetBuffer();
}

int main() {
  std::string s1{"hello"};
  std::string s2{std::move(s1)};
  std::cout << s1.size() << std::endl;
  std::cout << s2.size() << std::endl;
  test_move();
  test_rvalue();
  return 0;
}