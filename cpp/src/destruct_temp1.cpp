// Rust 语言是否反人类? - Some(me)的回答 - 知乎
// https://www.zhihu.com/question/328066906/answer/706929480
// 谨慎消除中间变量
#include <string>
#include <iostream>

int main() {

    std::string quote1("hello");
    const char *str1 = quote1.c_str();
    std::cout << str1 << std::endl;
    
    const char* str2 = std::string("C++ is anti-human").c_str();
    std::cout << str2 << std::endl;

    std::string quote2("I love Rust");
    const char* str3 = quote2.c_str();
    std::cout << str3 << std::endl;

    const char *str4 = std::string("Rust is good").c_str();
    std::cout << str4 << std::endl;
    return 0;
}