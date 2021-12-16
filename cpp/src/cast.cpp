//
// Created by Jiang Yinzuo on 2021/12/15.
//

#include <cstdio>

struct A {
  int a;
};

struct B {
  int b;
};

struct C : A, B {
  int c;
};

int main() {
  C o;

  o.a = 1;
  o.b = 2;
  o.c = 3;

  B *p1 = (B *)&o;
  B *p2 = static_cast<B *>(&o);
  B *p3 = reinterpret_cast<B *>(&o);
  B *p4 = dynamic_cast<B *>(&o);

  printf("self:             %p\n", reinterpret_cast<void *>(&o));
  printf("c conversion:     %p\n", reinterpret_cast<void *>(p1));
  printf("static_cast:      %p\n", reinterpret_cast<void *>(p2));
  printf("reinterpret_cast: %p\n", reinterpret_cast<void *>(p3));
  printf("dynamic_cast      %p\n", reinterpret_cast<void *>(p4));

  printf("o.b:              %d\n", o.b);
  printf("p1->b:            %d\n", p1->b);
  printf("p2->b:            %d\n", p2->b);
  printf("p3->b:            %d\n", p3->b);
  printf("p4->b:            %d\n", p4->b);

  C *p5 = reinterpret_cast<C *>(p2);
  C *p6 = static_cast<C *>(p2);
  C *p7 = (C *)(p2);
  printf("reinterpret_cast: %p\n", reinterpret_cast<void *>(p5));
  printf("static_cast:      %p\n", reinterpret_cast<void *>(p6));
  printf("c conversion:     %p\n", reinterpret_cast<void *>(p7));
  //  printf("p5->c:            %d\n", p5->c);
  printf("p6->c:            %d\n", p6->c);
  printf("p7->c:            %d\n", p7->c);
  return 0;
}