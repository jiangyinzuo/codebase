#include <iostream>
#include <string>

class Student {
public:
    std::string name;

    Student(std::string name) : name(name) {}

    std::string &get_name() {
        return name;
    }
};

int main() {
    std::string &name1 = Student("C++ is anti-human").get_name();

    std::cout << name1 << std::endl;

    std::string &name2 = Student("C++20").get_name();
    std::cout << name2 << std::endl;

    std::cout << Student("C++ is anti-human").get_name() << std::endl;
    return 0;
}