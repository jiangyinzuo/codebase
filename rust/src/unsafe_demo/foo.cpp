// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

// UB

#include <cstdio>
int* foo() {
    int a = 3;
    return &a;
}

int main() {
    int* p = foo();
    printf("%d\n", *p);
    return 0;
}