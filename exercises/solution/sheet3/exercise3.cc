#include <iostream>

#define EVAL(CHAR, EXPR) x=3; y=2; z=5; print("(" #CHAR ")", EXPR); print("x=",x,"y=",y,"z=",z)

void print() { std::cout << std::endl; }

template <class T0, class... T>
void print(T0 const& arg0, T const&... args) {
  std::cout << arg0 << ' ';
  print(args...);
}

int main()
{
  int x = 3, y = 2, z = 5;

  EVAL(a, (x / y) * z);
  EVAL(b, (x * (y++)) / (-z));
  EVAL(c, (x^(2 + y))^2);
  EVAL(d, (++x) * (x++)); // PROBLEM: order of evaluation!
  EVAL(e, ((*(&x))*y)&&z);
  EVAL(f, (x++)+x);

  EVAL(g, ((z-y)-x)?((x+y)+z):((x-y)-z));
  EVAL(h, (z<<x)>>y);
  EVAL(i, (z>>x)<<y);
  EVAL(j, x||(y|z));
  EVAL(k, (++x)*=(y++));
  EVAL(l, (-(~x))^x);
}