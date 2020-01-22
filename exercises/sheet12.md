# Exercise sheet 12 - 2020/01/22

## Exercise 1 (Functors)
Write a functor `Scale` that multiplies an assigned value with a constant factor. This constant factor
is stored as member variable in the functor and is initialized in the constructor. The `operator()` receives a
reference to the value and scales this argument (using pass-by-reference).

Use the STL algorithm `std::for_each` to scale the values of a `std::array`, or `std::vector`.

### Note
- The semantics of `std::for_each` is slightly different from the for-each implementation shown in the lecture. The functor
should not return the result, but change its argument that is passed-by-reference!
- In order to use `std::for_each` you need to include the header `<algorithm>`.

### Resources
- [cppreference:for_each](https://en.cppreference.com/w/cpp/algorithm/for_each)


## Exercise 2 (Iterators)
1. Write an iterator `integer_range_iterator` that always returns an integer on dereferencing and increments this
integer when incrementing the iterator. Thus, when you loop over all values of the iterator you get an
increasing sequence of numbers, without storing this sequence explicitly. Provide a constructor, that takes the
initial value of the integer that is incremented. Example of usage:
```c++
for (auto it = integer_range_iterator(0); it != integer_range_iterator(10); ++it)
  std::cout << *it << " ";
```
This should print
```
0 1 2 3 4 5 6 7 8 9
```
Implement the dereferencing operator, increment operator and comparison operators.

2. Write a *pseudo-container* `integer_range`, that has just two member functions `begin()` and `end()` returning
the `integer_range_iterator` of the begin and end of the container. The values begin and end should
be given in the constructor of the container.

### Note
- A word *pseudo-container* just here in this exercise refers to a container that does not store all its elements
  directly, but provide a way to iterate over all its values.
- (optional) In addition to the `begin()` and `end()` member-function, you could easily implement element-access functions
  `operator[]` and size functions for the `integer_range` container. What about mutable access functions? Can you implement
  the whole interface of a `std::vector`?


## Exercise 3 (Functor composition)
1 If you have functors that represent some mathematical functions like `sqr`, `sqrt`, `exp`, `tanh`,
... how could you combine these functors in order to build more complex operations. Mathematically spoken:
let $`f : A \to B`$ and $`g : B \to C`$ be two unary functors with `argument_types` $`A`$ and $`B`$, and `return_types` $`B`$
and $`C`$ respectively. Build a functor `Composer` that implements the composition $`f \circ g : A \to C, x \mapsto g(f(x))`$.

In order to do so, write a class `Composer` first that takes two constructor arguments representing the functors
for $`f`$ and $`g`$ and provide a free function that instantiates this class:
```c++
template <class F, class G>
class Composer
{
public:
  Composer(F const& f, G const& g) : (...) { ... }

  result_type operator()(argument_type const& x) const { ... }
private:
  // ...
};

template <class F, class G>
Composer<F,G> compose(F const& f, G const& g) {
  return Composer<F,G>(f,g);
}
```
Fill in the missing parts and specify `argument_type` and `result_type`.

3. (optinal) Write the composer class, using C++-Lambda expressions instead. See also
[CppTruths](http://cpptruths.blogspot.de/2014/03/fun-with-lambdas-c14-style-part-1.html) for possible
solutions.

### Note
- Instead of providing a *generator*-function to instantiate the class, you could rely on class-template-argument deduction of c++17.

### Resources
- [cccreference:class_template_argument_deduction](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)


## Exercise 4 (Algorithms)
What does the following algorithm implement?
```c++
template <class InputIt1, class InputIt2>
bool ALGORITHM1(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}
```
