namespace A {

  void foo() {}

  namespace B {

    // void foo() {}
    void foo(int) {}

  }

}


int main()
{
  A::foo();
  A::B::foo();
  A::B::foo(1);
}