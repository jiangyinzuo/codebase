# 书籍/教程/文档/工具
### 编译器文档
- [gcc文档](https://gcc.gnu.org/onlinedocs/)
- [clang文档](https://clang.llvm.org/docs/index.html#)

### 静态代码分析
参考资料：
- [cpp-best-practices](https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md)
#### clang-tidy
集成了一些规则，如
- [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines)

### 动态代码分析
#### Google Sanitizer
- https://github.com/google/sanitizers/wiki/AddressSanitizer
- [gcc 文档](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)
- [clang 文档](https://clang.llvm.org/docs/index.html#)
```
-O1 -fsanitize=address
```

### 汇编查看工具
- [godbolt](https://godbolt.org/)

### 博客
- [Cpp in Action](http://blog.gerryyang.com/c/c++/%E7%BC%96%E7%A8%8B%E8%AF%AD%E8%A8%80/2019/05/06/cpp-in-action.html)

# 编译器选项
## gcc编译器选项
- [gcc文档](https://gcc.gnu.org/onlinedocs/)
- [cpp-best-practices](https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md)
### Warning选项
```
-Werror \
-Wall -Wextra -Wnon-virtual-dtor -Wpedantic \
-Wunused -Wshadow -Woverloaded-virtual
```


# 声明、定义、类型转换、类型推导
### static const 类成员
```cpp
#include <iostream>

int min(const int &a, const int &b) { return a < b ? a : b; }

class Foo {
 public:
  static const int BAR = 42;
  void F1(int b) { min(Foo::BAR, 4); }
};
// const int Foo::BAR;
void F2(int b) { min(Foo::BAR, 4); }

int main() {
  const int *a [[maybe_unused]] = &Foo::BAR;
  std::cout << Foo::BAR << &Foo::BAR << std::endl;
  return 0;
}
```

以上代码的`Foo::BAR`只有声明，没有定义，这时候`Foo::BAR`没有具体存放该int常量的内存地址。因此对`Foo::BAR`取值不会报错，取地址/取引用时链接器会报 undefined reference to `Foo::BAR`的错误。添加`const int Foo::BAR;`定义后才能链接成功。

`void Foo::F1(int b)`会通过内联优化消除取引用的步骤，因此能链接通过。

编译器选项为-O0时，`void F2(int b)`不进行任何编译优化，无法链接通过。

假如开-O1以上优化，或者在F2声明中加`inline`关键字，`void F2(int b)`函数体将被内联优化，就不会对`Foo::BAR`取引用，F2就能链接通过。

假如将`int min(const int &a, const int &b)`的a改为`const int a`，直接取值，不取引用，F2也能链接通过。

但main函数中的`std::cout << Foo::BAR << &Foo::BAR << std::endl;`无论如何都不能进行编译优化。因此只有添加`const int Foo::BAR;`定义后才能链接成功。

Rust的const全局变量直接定义，没有分声明和定义两个步骤，因此无以上痛点。

### C++ 4种cast和C-style cast

参考资料：
- [# C++ Casting, or: “Oh No, They Broke Malloc!”](https://embeddedartistry.com/blog/2017/03/15/c-casting-or-oh-no-they-broke-malloc/)：**推荐阅读**
- [cpp reference: explicit_cast](https://en.cppreference.com/w/cpp/language/explicit_cast)：**C-style cast实际上按先后顺序进行了5种尝试**
- Effective C++ 条款27
- [C++的cast有四种cast法](https://zhuanlan.zhihu.com/p/151744661)
- [C++有了 static_cast 等四个 cast 类型转换，是不是就可以抛弃 C 的强制类型转换](https://www.zhihu.com/question/493328539)
- [reinterpret_cast这是C++的写法, 与直接(类名)有区别吗?](https://www.zhihu.com/question/468514838/answer/1967696567)
- [C++笔记 · C++类型转换](https://zhuanlan.zhihu.com/p/27966225)
- [cpp core guideline](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Pro-type-downcast)：过于保守，并不是很赞同

### 万能引用（universal reference）和引用折叠（引用坍缩，reference-collapsing）
universal reference又称为 #forwarding_reference（转发引用） 。
参考资料：
- https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

#### 完美转发
std::forwarding
decltype(auto) 模板函数返回值转发

### 类型推断（type dedution）

参考资料：
- [极客时间](https://time.geekbang.org/column/article/176850)
- [现代C++教程](https://changkun.de/modern-cpp/zh-cn/02-usability/#decltype)

#### auto
#### decltype
#### decltype(auto)

# 构造、拷贝、移动
### 两段构造
因为构造函数没有返回值，第一段构造用于初始化普通的成员。第二段成员函数（通常命名为Init）负责初始化各种可能出错的资源。
不要将未构造完的对象指针（特别是this指针）传给其它函数。尤其是在多线程环境，更容易出错。

Rust只需用一个函数返回和类型（sum type）来处理“返回正确构造的类or错误信息”的情况，因此不需要两段构造。

### 析构函数释放文件、锁等资源的函数需要禁用拷贝构造函数
否则拷贝后容易提前释放/多次释放资源，引发系统bug。

### 手动调用了析构函数的对象再次被使用似乎是UB
[virtual_method.cpp](src/virtual_method.cpp)

# 设计模式

## 单例模式

线程安全的懒汉式单例模式最佳实践示例见：
[singleton.cpp](src/singleton.cpp)

参考资料：
- https://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
- https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
- [Cpp in Action](http://blog.gerryyang.com/c/c++/%E7%BC%96%E7%A8%8B%E8%AF%AD%E8%A8%80/2019/05/06/cpp-in-action.html#%E5%8F%8C%E9%87%8D%E6%A3%80%E6%9F%A5%E9%94%81%E5%AE%9A)