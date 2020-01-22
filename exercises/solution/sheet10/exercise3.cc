#include <iostream>

class SuperClass
{
public:
  void foo() const
  {
    std::cout << "SuperClass::foo" << std::endl;
  }
};

class DerivedClass : public SuperClass
{
public:
  void foo() const  // must be marked const
  {
    std::cout << "DerivedClass::foo" << std::endl;
  }
};

class LeafClass : public DerivedClass   // must be derived public
{
public:
  void bar()
  {
    foo();
  }
};

void test(SuperClass const& super)
{
  super.foo();
}

int main()
{
  SuperClass super;
  DerivedClass derived;
  LeafClass leaf;

  super.foo();

  derived.foo();
  test(derived);

  leaf.bar();
  test(leaf);
}
