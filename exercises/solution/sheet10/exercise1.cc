#include <list>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <iterator>
#include <typeinfo>
#include <iostream>
#include <algorithm>

#include "Timer.hh"

namespace scprog
{
  // class-template that represents a list of types
  template <class...>
  struct Types {};

  // Represents a compound value type
  struct A
  {
    short s = 0;
    int i = 0;
    char c = '0';
  };

  // comparison of objects of type `A`
  inline bool operator<(A const& lhs, A const& rhs)
  {
    return std::tie(lhs.s, lhs.i, lhs.c) < std::tie(rhs.s, rhs.i, rhs.c);
  }

  // generate random values
  template <class T>
  struct Generator
  {
    Generator(int a = -125, int b = 125)
      : a_(a), b_(b)
    {}

    T operator()() const
    {
      return T(a_ + std::rand() % (b_ - a_ + 1));
    }

    int a_;
    int b_;
  };

  // specialization for type `A`
  template <>
  struct Generator<A>
  {
    Generator(int a = -125, int b = 125)
      : gen_s(a,b)
      , gen_i(a,b)
      , gen_c(a,b)
    {}

    A operator()() const
    {
      return {gen_s(), gen_i(), gen_c()};
    }

    Generator<short> gen_s;
    Generator<int> gen_i;
    Generator<char> gen_c;
  };


  // type traits to test for push_front method
  // ---------------------------------------------------------------------------

  struct true_type {};
  struct false_type {};

  template <class C>
  struct has_push_front : false_type {};
  template <class T>
  struct has_push_front<std::list<T>> : true_type {};
  template <class T>
  struct has_push_front<std::deque<T>> : true_type {};


  // output of types
  // ---------------------------------------------------------------------------

  template <class T>
  std::ostream& operator<<(std::ostream& out, Types<std::list<T>>)
  {
    return out << "list<" << typeid(T).name() << ">";
  }

  template <class T>
  std::ostream& operator<<(std::ostream& out, Types<std::vector<T>>)
  {
    return out << "vector<" << typeid(T).name() << ">";
  }

  template <class T>
  std::ostream& operator<<(std::ostream& out, Types<std::deque<T>>)
  {
    return out << "deque<" << typeid(T).name() << ">";
  }


  // algorithms
  // ---------------------------------------------------------------------------

  template <class T>
  void sort(std::list<T>& l) { l.sort(); }

  template <class T>
  void sort(std::vector<T>& v) { std::sort(v.begin(), v.end()); }

  template <class T>
  void sort(std::deque<T>& v) { std::sort(v.begin(), v.end()); }


  // create, fill and sort a container
  // ---------------------------------------------------------------------------

  // the actual test
  template <class Container, class Inserter>
  void test(std::size_t n, true_type)
  {
    // the type of the elements stored in the container
    using T = typename Container::value_type;

    // 1. create an empty container
    Container c;

    // 2. fill the container with random values
    Timer t;
    std::generate_n(Inserter(c),
      n, Generator<T>{});
    std::cout << "time fill (" << Types<Container>{} << "): " << t.elapsed() << "\n";

    // 3. sort the values based on operator< comparison
    t.reset();
    sort(c);
    std::cout << "time sort (" << Types<Container>{} << "): " << t.elapsed() << "\n";
  }

  // fallback for types not providing insertion method
  template <class Container, class Inserter>
  void test(std::size_t n, false_type) {} // do nothing


  // calls test for push_back and push_front on all container types
  template <class Container, class... Containers>
  void test_containers(Types<Container, Containers...>, std::size_t n)
  {
    std::srand(123);
    std::cout << "push_back:\n";
    test<Container, std::back_insert_iterator<Container>>(n, true_type{});

    std::srand(123);
    std::cout << "push_front:\n";
    test<Container, std::front_insert_iterator<Container>>(n, has_push_front<Container>{});

    // tail recursion
    test_containers(Types<Containers...>{}, n);
  }

  // fallback for an empty list of types
  void test_containers(Types<>, std::size_t n) {} // do nothing


} // end namespace scprog


int main()
{
  using Containers = scprog::Types<
    std::list<int>, std::list<double>, std::list<scprog::A>,
    std::vector<int>, std::vector<double>, std::vector<scprog::A>,
    std::deque<int>, std::deque<double>, std::deque<scprog::A> >;

  scprog::test_containers(Containers{}, 1e6);
}
