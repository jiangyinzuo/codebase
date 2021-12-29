//
// Created by Jiang Yinzuo on 2021/12/28.
//

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <utility>

class FileWithPos {
 public:
  FileWithPos() = default;

  FileWithPos(FileWithPos &&other) noexcept : fd_(other.fd_), pos_(other.pos_) {
    other.fd_ = -1;
    other.pos_ = 0;
  }

  FileWithPos(const FileWithPos &) = default;

  ~FileWithPos() {
    if (fd_ != -1) {
      ::close(fd_);
      fd_ = -1;
      pos_ = 0;
    }
  }

  bool Open(const char *path) {
    fd_ = ::open(path, O_CREAT | O_RDWR, 0644);
    return fd_ >= 0;
  }

  bool Write(char buf[], off_t length) {
    while (length > 0) {
      int written = ::write(fd_, buf, length);
      if (written == -1 && errno != EINTR) {
        return false;
      } else {
        length -= written;
      }
    }
    pos_ += length;
    return true;
  }

  off_t Pos() const { return pos_; }

 private:
  int fd_{-1};
  off_t pos_{0};
};

template <typename T>
concept Writable = requires(T t) {
  { t.Write((char *)"", 0) } -> std::same_as<bool>;
};

void WriteHello(Writable auto file_with_pos) {
  if (!file_with_pos.Write(const_cast<char *>("hello"), 5)) {
    perror("WriteHello");
    exit(EXIT_FAILURE);
  }
}

int main() {
  FileWithPos file_with_pos;
  if (!file_with_pos.Open("./hello.txt")) {
    perror("Open");
    exit(EXIT_FAILURE);
  }
  WriteHello(file_with_pos);
  FileWithPos &&file_with_pos1 = std::move(file_with_pos);
  WriteHello<FileWithPos &&>(
      std::forward<FileWithPos>(file_with_pos1));  // Bad file descriptor
  return 0;
}
