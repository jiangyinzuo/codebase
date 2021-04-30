# CPP Trick

## 模板

1.

编译错误

```c++
template <typename T>
class A {
};

template <typename T>
void foo(A<T> a) {
}

void bar(int b) {
  foo(b); // error: no matching function for call to 'foo'
}
```

编译成功，但实际上`Foo::bar`方法有问题

```c++
template<typename T>
class A {
};

template<typename T>
class Foo {
  public:
    void foo(A<T> a) {
    }
    void bar(int a) {
      foo(a);
    }
};

int main() {
  return 0;
}
```

编译错误

```c++
template<typename T>
class A {
};

template<typename T>
class Foo {
  public:
    void foo(A<T> a) {
    }
    void bar(int a) {
      foo(a);
    }
};

int main() {
  Foo<int> f;
  f.bar(3); // error: no viable conversion from 'int' to 'A<int>'
  return 0;
}
```