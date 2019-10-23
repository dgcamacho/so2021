int x = 11;  // (0) globale variable x

void f() {   // function scope
  int x;     // (1) local x hiding global x
  x = 1;     // assignment to local x (1)
  {
    int x;   // (2) hides local x (1)
    x = 2;   // assignment ot local x (2)
  }
  x = 3;     // assignment to local x (1)
}

void f2() {  // function scope
  int y = x; // use global x
  int x = 1; // (3) hides the global x
  ::x = 2;   // assignment to global x
  y = x;     // use local x (3)
  x = 2;     // assignment to local x (3)
}

int main()
{
  f();
  f2();
}