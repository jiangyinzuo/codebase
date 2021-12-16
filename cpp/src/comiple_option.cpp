//
// Created by Jiang Yinzuo on 2021/12/15.
//

#include <cstdio>
#include <string>

class Shape {
 public:
  virtual ~Shape() = default;
  virtual const std::string& Name() = 0;
};

class Triangle : public Shape {
 public:
  Triangle() : name_("triangle") {}
  ~Triangle() { puts("delete triangle"); }
  const std::string& Name() override;

 private:
  std::string name_;
};

const std::string& Triangle::Name() { return name_; }

int main() {
  Shape* s = new Triangle();
  puts(s->Name().c_str());

  Shape* s2 = new Triangle();
  delete s2;
  delete s2;
  return 0;
}