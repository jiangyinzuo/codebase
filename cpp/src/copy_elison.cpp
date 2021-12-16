// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.
#include <iostream>
struct ImageNumber {
  int real, image;
  ImageNumber(int real, int image) : real(real), image(image) {
    std::cout << "construct" << std::endl;
  }
  ImageNumber(const ImageNumber &image_number)
      : real(image_number.real), image(image_number.image) {
    std::cout << "copy" << std::endl;
  }
  ImageNumber(ImageNumber &&image_number) noexcept
      : real(image_number.real), image(image_number.image) {
    std::cout << "move" << std::endl;
  }
};

class Container {
 public:
  explicit Container(ImageNumber &&number) : image_number_(std::move(number)) {}
  void PrintImageNumber() const {
    std::cout << image_number_.real << image_number_.image << std::endl;
  }

 private:
  ImageNumber image_number_;
};

int main() {
  ImageNumber image_number{3, 4};
  Container c(std::move(image_number));
  c.PrintImageNumber();
  return 0;
}