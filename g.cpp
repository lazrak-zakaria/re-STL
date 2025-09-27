#include<stdio.h>
#include <iostream>
#include <deque>


template <class T>
struct is_pointer
{
  template <class U>
  static char is_ptr(U *);

  template <class X, class Y>
  static char is_ptr(Y X::*);

  template <class U>
  static char is_ptr(U (*)());

  static double is_ptr(...);

  static T t;
  enum { value = sizeof(is_ptr(t)) == sizeof(char) };
};

struct Foo {
  int bar;
};

int main(void)
{
  int j = - 1;
  unsigned long long h = 333;
  if (j < int(h))
    std::cout << "ok\n";
  

}