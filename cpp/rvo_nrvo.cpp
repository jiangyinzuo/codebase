//
// Created by Jiang Yinzuo on 2020/9/28.
// g++ -fno-elide-constructors foo.cpp -o foo.exe  禁止RVO/NRVO
// g++ foo.cpp -o foo.exe

#include <iostream>
#include <string>

class A {
public:
    std::string s;

    explicit A(const char *s) {
        this->s = s;
        std::cout << "construct" << std::endl;
    }

    ~A() {
        std::cout << "destruct" << std::endl;
    }

    A(const A &a) {
        this->s = a.s;
        std::cout << "copy" << std::endl;
    }

    A(A &&) = default;

//    A(A &&a) {
//        this->s = a.s;
//        std::cout << "moved" << std::endl;
//    }

    A &operator=(const A &a) {
        this->s = a.s;
        std::cout << "=" << std::endl;
        return *this;
    }

    A &operator=(A &&a) {
        this->s = a.s;
        std::cout << "=move" << std::endl;
        return *this;
    }
};

A foo() {
    A a("hello");
    std::cout << "--------" << std::endl;
    return a;
}

int main() {
    A a = foo();
    std::cout << "--------" << std::endl;
    A &&a2 = std::move(a);
    std::cout << "--------" << std::endl;
    std::cout << a2.s << std::endl;
    return 0;
}