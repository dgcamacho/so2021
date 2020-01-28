# Exercise sheet 13 - 2020/01/28

## Exercise 1 (Iterators)
Given the following for statement:
```c++
for (int i = 0; i < max_length; ++i)
  if (line[i] == ' ')
    space_count++;
```
Assume that line is a `std::vector`. Rewrite the `for` statement so it instead steps through `line` using a
vector iterator.


## Exercise 2 (Iterators)
Do the following on a container, e.g. a `std::vector`, with `int`s, using standard function objects, function
adapters, algorithms, and maybe also some own function objects:
1. Find all values which are larger than a certain value.
2. Find all values which are not equal to certain value.
3. Multiply all values with a certain factor.


## Exercise 3 (Iterators)
In *python* operations on ranges are a fundamental concept and make the language very nice to use. An
example is the `map` operation, that takes a range and applies a functor to each element, when traversing the
range:
```python
for x in map(lambda x: 2*x, range(0,10)):
  print x
```
Here, an integer range `[0, 10)` is created and the entries are scaled by a factor 2, but only during iteration in
the loop. We want to implement something similar in C++:
- take a functor and a range,
- provide iterators over the range and
- return on dereferencing the mapped value

Therefore, write a class `MappedRange<Functor,Range>` with a constructor that stores a functor, gets a range
and stores iterators to begin and end of the range:
```c++
MappedRange(Functor f, Range const& range)
  : f_(f)
  , it_(range.begin())
  , end_(range.end())
{}
```
What are the types of the stored iterators? Then, implement a class `MappedIterator` that contains `operator++`,
`operator==`, and `operator!=` implemented in terms of the original range iterators! Finally, implement a new
dereferencing operation `operator*`, by returning the mapped dereferenced range iterator.
```c++
auto operator*() const {
  return f_(*it_);
}
```
This `MappedIterator` needs the functor and a range iterator to work with. Write member-functions `begin()`
and `end()` in the class `MappedRange` that return a `MappedIterator`.

To create an instance of the class `MappedRange` write a generator function, i.e., a function template that just instantiates
the class:
```c++
template <class Functor, class Range>
MappedRange<Functor, Range> map(Functor f, Range const& range)
{
  /* implementation here */
}
```
Try out your implementation with a vector and a list filled with some values, or with the integer-range
from exercise sheet 12.


## Exercise 4 (Iterators)
Provide an iterator for the class `Vector` of sheet 9. Therefore Implement a new class for the vector iterators
that is instantiated and returned in the two member function `begin()` and `end()` in the class `Vector`. This iterator
class needs a constructor with the address of the data, a dereferencing operator, increment and decrement operator and
comparison operators. See also http://www.cplusplus.com/reference/iterator/iterator as a reference implementation of a
user defined iterator.

Test your iterator with some algorithms from the standard library


## Exercise 5 (Algorithms)
What does the following algorithm implement?
```c++
template <class ForwardIt>
ForwardIt ALGORITHM2(ForwardIt first, ForwardIt last)
{
  if (first == last)
    return last;

  ForwardIt result = first;
  while (++first != last) {
    if (!(*result == *first) && ++result != first) {
      *result = *first; // or: ... = std::move(*first)
    }
  }
  return ++result;
}
```
