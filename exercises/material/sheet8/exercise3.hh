#include <iostream>
#include <typeinfo>

// function template returning the identity element of type T
template <class T>
T identity();

// function template returning a random element of type T
template <class T>
T random();


// a + b can be assigned to a type T
template <class T>
bool test_closure(T const& a, T const& b)
{
  T c{ a + b }; // construction from a + b
  c = a + b;    // assignment to T
  return true;
}

// for all a,b,c the associativity law holds
template <class T>
bool test_associativity(T const& a, T const& b, T const& c)
{
  return (a + b) + c == a + (b + c);
}

// the order of the operands can be interchanged
template <class T>
bool test_commutativity(T const& a, T const& b)
{
  return a + b == b + a;
}

// there exists an identity element
template <class T>
bool test_identity(T const& a)
{
  T e{ identity<T>() };
  return (e + a == a) && (a + e == a);
}

// for all elements a there exists an inverse element -a
template <class T>
bool test_inverse(T const& a)
{
  T inv_a{ -a };
  T e{ identity<T>() };
  return (a + inv_a == e) && (inv_a + a == e);
}


template <class T>
bool test()
{
  bool has_closure = true;
  bool has_associativity = true;
  bool has_commutativity = true;
  bool has_identity = true;
  bool has_inverse = true;

  // run a test with random data 100 times
  for (int i = 0; i < 100; ++i) {
    T a{ random<T>() };
    T b{ random<T>() };
    T c{ random<T>() };

    has_closure = has_closure && test_closure(a,b);
    has_associativity = has_associativity && test_associativity(a,b,c);
    has_commutativity = has_commutativity && test_commutativity(a,b);
    has_identity = has_identity && test_identity(a);
    has_inverse = has_inverse && test_inverse(a);
  }

  std::cout << "The type T=" << typeid(T).name() << " has the following properties:" << std::endl;
  std::cout << "  closure: "        << has_closure << std::endl;
  std::cout << "  associativity: "  << has_associativity << std::endl;
  std::cout << "  commutativity: "  << has_commutativity << std::endl;
  std::cout << "  identity: "       << has_identity << std::endl;
  std::cout << "  inverse: "        << has_inverse << std::endl;

  return has_associativity && has_closure && has_inverse && has_identity && has_commutativity;
}
