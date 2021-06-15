---
class: center, middle
# The C++ Standard Library

.footnote[Slides partially extracted from "*Systems Programming in C++*" (T. Neumann, M. Freitag, M. Sichert)]
---

# The C++ Standard Library

Provides a collection of useful C ++ classes and functions
- Is itself implemented in C ++
- Part of the ISO C ++ standard
  * Defines interface, semantics and contracts the implementation has to abide by (e.g. runtime complexity)
  * Implementation is not part of the standard
  * Multiple vendors provide their own implementations
  * Best known: `libstdc++` (used by gcc) and `libc++` (used by llvm)
  * formerly known as *Standard Template Library* (SGI)
- All features are declared within the `std` namespace
- Functionality is divided into sub-libraries each consisting of multiple headers
- Includes parts of the C standard library

---

# The C++ Standard Library
We will look into
- Containers: e.g. `array`, `vector`, `unordered_map`, `map`
- Iterators
- Algorithms: (stable) sort, search, max, min, ...
- Numerics
  * Common mathematics functions (`sqrt`, `pow`, `mod`, `log`, ...)
  * Complex numbers
  * Random number generation
- I/O
  * Input-/Output streams
  * File streams
  * String streams

---

# The C++ Standard Library
## Containers - A Short Overview
A container is an object that stores a collection of other objects
- Manage the storage space for their elements
- Generic: The type(s) of elements stored are template parameter(s)
- Provide member functions for accessing elements directly, or through *iterators*
- Make guarantees about the complexity of their operations:
  .font-md[<ul>
  <li> Sequence containers (e.g. <code class="remakr-inline">std::array</code>, <code class="remakr-inline">std::vector</code>, <code class="remakr-inline">std::list</code>):
    Optimized for sequential access </li>
  <li> Associative containers (e.g. <code class="remakr-inline">std::set</code>, <code class="remakr-inline">std::map</code>): Sorted, optimized for
    search \(\mathcal{O}(\log n)\) </li>
  <li> Unordered associative containers (e.g. <code class="remakr-inline">std::unordered_set</code>,
    <code class="remakr-inline">std::unordered_map</code>): Hashed, optimized for search (amortized: \(\mathcal{O}(1)\),
    worst case: \(\mathcal{O}(n)\) ) </li>
  </ul>]

> .h3[Guideline:] Use standard containers whenever possible! When in doubt, use `std::vector`!

---

# The C++ Standard Library
## Containers - Common Interface
- All container types share some common functionality
- Requirements are formulated as written concepts \(\to\) [cppreference](https://en.cppreference.com/w/cpp/named_req/Container)

**Requirements:**
`C` container type; `T` element type; `a`, `b` objects of type `C`

**Associated Types:**
```c++
using value_type = T;                     // type of the elements stored
using reference = T&;
using const_reference = T const&;
using iterator = <impl_defined>;          // (constant) iterator pointing to `T`
using const_iterator = <impl_defined>;    // a model of *ForwardIterator*
using difference_type = <signed_integer>;
using size_type = <unsigned_integer>;     // large enough to represent all pos. values
                                          // of `difference_type`
```

---

# The C++ Standard Library
## Containers - Common Interface
**Requirements:**
`C` container type; `T` element type; `a`, `b` objects of type `C`

**Methods and operators:**
```c++
C ();         // default constructor
C (a);        // copy constructor
a = b;        // copy assignment
a.begin()     // Iterator to the first element of a
a.end()       // Iterator to one past the last element of a
a == b;       // Comparison for equality
a != b;       // !(a == b)
a.swap(b);    // exchanges the values of a and b
swap(a,b);    // a.swap(b)
a.size();     // Number of elements stored in the container
a.max_size(); // b.size() where b is the largest possible container
a.empty();    // Check whether no element is stored
```

---

# The C++ Standard Library - `std::vector`
Vectors are arrays that can dynamically grow in size. Defined in the header [`<vector>`](https://en.cppreference.com/w/cpp/container/vector)
- Elements are still stored contiguously
- Elements can be inserted and removed at any position \(\to\) `insert()`, `erase()`
- Preallocates memory for a certain amount of elements
- Allocates new, larger chunk of memory and moves elements when mem. is exhausted
-  Memory for a given amount of elements can be reserved \(\to\) `reserve()`
- Time complexity:
  * Random access: \(\mathcal{O}(1)\)
  * Insert and remove at the end: Typically \(\mathcal{O}(1)\), worst case: \(\mathcal{O}(n)\) (possible reallocation)
  * Insert and remove at any other position: \(\mathcal{O}(n)\)
- Access to the underlying C-style data array with `data()` member function

---

# The C++ Standard Library - `std::vector`
## Accessing Elements
Vectors are constructed just like arrays:
```c++
std::vector<int> fib = {1,1,2,3};
```
Access elements via array notation, or through a raw pointer:
```c++
fib[1] // == 1;
int* fib_ptr = fib.data();
fib_ptr[2] // == 3;
```
Update elements via array notation, or through a raw pointer:
```c++
fib[3] = 43;
fib[2] = 42;
fib.data()[1] = 41; // fib is now 1, 41, 42, 43
```
**Note:** It is not possible to insert new elements this way! You can only update
existing ones.

---

# The C++ Standard Library - `std::vector`
## Inserting and Removing Elements
Insert or remove elements at the end in constant time:
```c++
fib.push_back(5);         // fib is now 1, 1, 2, 3, 5
int my_fib = fib.back();  // my_fib is 5
fib.pop_back();           // fib is 1, 1, 2, 3
```
Inserted or remove elements anywhere with an iterator pointing at the element
after insertion, or the element to be erased respectively:
```c++
auto it = fib.begin(); it += 2;
fib.insert(it, 42);       // fib is now 1, 1, 42, 2, 3
it = fib.begin(); it +=2; // insertion invalidated the iterator, get a new one
fib.erase(it);            // fib is now again 1, 1, 2, 3
```
Empty the whole vector with clear:
```c++
fib.clear();  // no memory is released, just size changed
fib.empty();  // true
fib.size();   // == 0
```

---

# The C++ Standard Library - `std::vector`
## Reserving memory
If the final size of a vector is already known, give the vector a hint to avoid
unnecessary reallocations:
```c++
std::vector<int> vec;
vec.reserve(1000000);   // enough space for 1'000'000 elements is allocated
vec.capacity();         // == 1'000'000
vec.size();             // == 0, do not mix this up with capacity!
for (int i = 0; i < 1000000; ++i)
  vec.push_back(i);     // no reallocations in this loop!
```
If the vector won't grow in the future, reduce its capacity to save unused space:
```c++
std::vector<int> vec;
vec.reserve(100);       // Reserve some space to be sure
// Turns out, we only needed a capacity of 10
for (int i = 0; i < 10; ++i)
  vec.push_back(i);
// Free the space for the other 90 elements we reserved but didn't need
vec.shrink_to_fit();
```

---

# The C++ Standard Library - `std::unordered_map`
Maps are associative containers consisting of key-value pairs
- Defined in the header [`<unordered_map>`](https://en.cppreference.com/w/cpp/container/unordered_map)
- Keys are required to be unique
- At least two template parameters: `Key` and `T` (type of the values)
- Is internally a hash table
- Amortized \(\mathcal{O}(1)\) complexity for random access, search, insertion, and removal
- No way to access keys or values in order (use `std::map` for that!)
- Accepts custom hash- and comparison functions through third and fourth template parameter

> .h3[Guideline:] Use `std::unordered_map` if you need a hash table, but don't need ordering

---

# The C++ Standard Library - `std::unordered_map`
## Accessing Elements
Maps can be constructed pairwise:
```c++
std::unordered_map<std::string, double> name_to_grade {
  {"maier", 1.3},  {"huber", 2.7},  {"schmidt", 5.0}
};
```
Lookup the value to a key with C-style array notation, or with `at()` :
```c++
name_to_grade["huber"]; // == 2.7
name_to_grade.at("schmidt"); // == 5.0
```
A map can also be searched for with find :
```c++
auto search = name_to_grade.find("schmidt");
if (search != name_to_grade.end()) {
  // Returns an iterator pointing to a pair!
  search->first;  // == "schmidt"
  search->second; // == 5.0
}
```

---

# The C++ Standard Library - `std::unordered_map`
## Accessing Elements

To check if a key exists, use `count()` that either returns 0 or 1:
```c++
name_to_grade.count("schmidt");  // == 1
name_to_grade.count("blafasel"); // == 0
```

## Insertion and Removal
Update or insert elements like this:
```c++
name_to_grade["musterfrau"] = 3.0;
```

In contrast to vectors, the array-notation also allows the insertion of new KV-pairs!
```c++
std::pair<std::string, double> pair("mueller", 1.0);
name_to_grade.insert(pair);
name_to_grade.insert({"mustermann", 3.7});  // construct the pair directly
name_to_grade.emplace("gruber", 1.7);       // construct the element in place
```

---

# The C++ Standard Library - `std::unordered_map`
## Insertion and Removal

Erase elements with `erase()` or empty the container with `clear()`:
```c++
auto search = name_to_grade.find("schmidt");
name_to_grade.erase(search);  // removes the pair with "schmidt" as key
name_to_grade.clear();        // removes all elements of name_to_grade
```

---

# The C++ Standard Library - `std::map`
In contrast to unordered maps, the keys of `std::map` are sorted
- Defined in the header [`<map>`](https://en.cppreference.com/w/cpp/container/map)
- Interface largely the same to `std::unordered_map`
- Optionally accepts a custom comparison function as template parameter
- Is internally a tree (usually something like R/B-Tree)
- \(\mathcal{O}(\log n)\) complexity for random access, search, insertion, and removal

> .h3[Guideline:] Use `std::map` only if you need a sorted associative container

---

# The C++ Standard Library
## Other Container Classes
Not described here are:
- `std::multimap`: similar to `std::map` but allows different elements with same index,
- `std::unordered_set`, `std::set`: stores unique elements,
- `std::queue`: container for FIFO (first-in first-out) access,
- `std::stack`: container for LIFO (last-in first-out) access,
- `std::priority_queue`: a container type, where the first element is always the greatest with
  respect to some defined order.
- `std::list`, `std::forward_list`: doubly-linked or singe-linked list.

---

# The C++ Standard Library
## Iterators: A Short Overview
Iterators are objects that can be thought of as pointer abstractions
- **Problem:** Different element access methods for each container
- **Therefore:** Container types not easily exchangeable in code
- **Solution:** Iterators abstract over element access and provide pointer-like
  interface
- Allow for easy exchange of underlying container type
- The standard library defines multiple iterator types as containers have varying
  capabilities (random access, traversable in both directions, ...)

---

# The C++ Standard Library - Iterator Example
All containers have a *begin* and an *end* iterator:
```c++
std::vector<std::string> vec = {"one", "two", "three", "four"};
auto it = vec.begin();
auto end = vec.end();
```
The *begin* iterator points to the first element of the container:
```c++
std::cout << *it; // prints "one"
std::cout << it->size(); // prints 3
```
The end iterator points to the first element **after** the container. Dereferencing it
results in undefined behavior:
```c++
*end; // undefined behavior
```
An iterator can be incremented (just like a pointer) to point at the next element:
```c++
++it; // Prefer to use pre-increment
std::cout << *it; // prints "two"
```

---

# The C++ Standard Library - Iterator Example
Iterators can be checked for equality. Comparing to the *end* iterator is used to
check whether iteration is done:
```c++
// prints "three,four,"
while (it != end) {
  std::cout << *it << ",";
  it++;
}
```
This can be streamlined with a range-based for loop:
```c++
for (auto elem : vec)
  std::cout << elem << ","; // prints "one,two,three,four,"
```
Such a loop requires the range expression (here: `vec`) to have a `begin()` and
`end()` member \(\to\) later more

---

# The C++ Standard Library - Iterator Example
Iterators can also simplify dynamic insertion and deletion:
```c++
for (auto it = vec.begin(); it != vec.end(); ++it) {
  if (it->size() == 3) {
    it = vec.insert(it,"foo");
    // it now points to the newly inserted element
    ++it;
  }
}
//vec == {"foo", "one", "foo", "two", "three", "four"}

for (auto it = vec.begin(); it != vec.end(); ++it) {
  if (it->size() == 3) {
    it = vec.erase(it);
    // erase returns a new, valid iterator
    // pointing at the next element
  }
}
//vec == {"three", "four"}
```

---

# The C++ Standard Library
## Range-based for-loops
Iterating over a (standard) container follows a common pattern: iterate from begin to end by
incrementing the iterator and dereference to get the element. This pattern got its own language syntax:

```c++
for (<range_declaration> : <range_expr>)
  <loop_statement>
```

`<range_declaration>`
: a declaration of a named variable, whose type is the type of the element of the sequence represented
   by `<range_expr>`, or a reference to that type.

`<range_expr>`
: any expression that represents a suitable sequence (either an array or an object for which `begin()`
  and `end()` member/free functions are defined), or a brace-init-list.

`<loop_statement>`
: any statement, typically a compound statement, which is the body of the loop. Can use the declared variable
  from the `<range_declaration>`.

---

# The C++ Standard Library
## Range-based for-loops
The generic implementation/translation:
```c++
{
  auto && __range = <range_expr>;
  auto __begin = <begin_expr>;
  auto __end = <end_expr>;
  for ( ; __begin != __end; ++__begin) {
    <range_declaration> = *__begin;
    <loop_statement>
  }
}
```
with `<begin_expr>` (and `<end_expr>`) an evaluation of `begin(__range)` or `__range.begin()`
(and `end(__range)` or `__range.end()`)

---

# The C++ Standard Library
## Range-based for-loops - Example
Take the element either by explicit type or `auto` placeholder type
```c++
std::vector<double> v = {1.0, 2.0, 3.0};
for (auto& v_i : v)
  v_i *= 2;
for (double v_i : v)
  std::cout << v_i << ",";
```

A `std::map` (or `std::unordered_map`) gives on dereferenced iterators the key-value pair:
```c++
std::map<std::string, double> m{ {"one", 1.0}, {"two", 2.0}, {"three", 3.0} };
for (auto const& elem : m) {
  std::cout << elem.first << " => " << elem.second << std::endl;
}
```

---

# The C++ Standard Library
## InputIterator and OutputIterator
Input- and OutputIterator are the most basic iterators. They have the following
features:
- Dereferencable with the `*` and `->` operators
- Incrementable, to point at the next element in sequence
- A dereferenced *InputIterator* can only by read
- A dereferenced *OutputIterator* can only be written to

As the most restrictive iterators, they have a few limitations:
- Single-pass only: Each element can be accessed only once
- Can only be incremented by one (i.e. it + 2 does not work)

Used in single-pass algorithms such as `find()` (InputIterator) or `copy()`
(Copying from an *InputIterator* to an *OutputIterator*)

---

# The C++ Standard Library
### InputIterator [`std::input_iterator`](https://en.cppreference.com/w/cpp/iterator/input_iterator)
- `operator++ ()` : pre-increment
- `operator++ (int)` : post-increment
- `operator* () const` : non-mutable dereference
- `operator-> () const` : non-mutable dereference with pointer access syntax

### OutputIterator [`std::output_iterator`](https://en.cppreference.com/w/cpp/iterator/output_iterator)
- `operator++ ()` : pre-increment
- `operator++ (int)` : post-increment
- `operator* ()` : mutable dereference
- `operator-> ()` : mutable dereference with pointer access syntax

---

# The C++ Standard Library
## Iterator categories
Iterators are categorized by its properties, either access (see *InputIterator* and *OutputIterator*),
by its traversal directions (*ForwardIterator*, *BidirectionalIterator*, *RandomAccessIterator*) or other
guarantees (e.g. *ContiguousIterator*)

### ForwardIterator [`std::forward_iterator`](https://en.cppreference.com/w/cpp/iterator/forward_iterator)
*ForwardIterator* is an *InputIterators* that allows multiple passes through the range
and can be compared for equality:
- `operator== ()`, `operator!= ()`: comparison of iterators

### BidirectionalIterator [`std::bidirectional_iterator`](https://en.cppreference.com/w/cpp/iterator/bidirectional_iterator)
A *BidirectionalIterator* is a *ForwardIterator* that additionally allows decrementing
- `operator-- ()` pre-decrement, `operator-- (int)` post-decrement

---

# The C++ Standard Library
### RandomAccessIterator  [`std::random_access_iterator`](https://en.cppreference.com/w/cpp/iterator/random_access_iterator)
*RandomAccessIterator* generalizes *BidirectionalIterator*:
- Additionally allows random access with `operator[]`
- Supports relational comparison operators, such as `<` or `>=`
- Can be incremented or decremented by any amount (i.e. `it + 2` does work)

### ContiguousIterator [`std::contiguous_iterator`](https://en.cppreference.com/w/cpp/iterator/contiguous_iterator)
- Introduced with C++17
- Guarantees that elements are stored in memory contiguously
- Formally: For every iterator `it` and integral value `n`: if `it + n` is a valid
  iterator, then `∗(it + n) == ∗(std::addressof(∗it) + n)`
- Orthogonal to all other iterators (i.e. a *ContiguousIterator* is not necessarily a *RandomAccessIterator*)

---

# The C++ Standard Library
## Algorithms with Iterators

Iterators can be used to have a general way to loop over containers. Algorithms can thus be implemented
for general input ranges.

In a classical programming style where algorithms are implemented for a specific data structure:
If we want to implement `m` algorithms for `n` container types

\[
  m \cdot n\text{ implementations}
\]

whereas for algorithms based on iterators, one just needs

\[
  m + n\text{ implementations}
\]

> .h3[Principle:] Decouple the implementation of data structures and algorithms.

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Accumulate the values in a container

```c++
template <typename Iterator, typename T>
T accumulate (Iterator first, Iterator last, T init)
{
  T sum(init);
  for (; first != last; ++it)
    sum = sum + *it;
  return sum;
}
```
Can be called on any container type
```c++
std::vector<double> vec{1.0,2.0,3.0,4.0,5.0};
double sum_d = accumulate(vec.begin(), vec.end(), 0.0);

std::list<int> l{5,4,3,2,1};
int sum_i = accumulate(l.begin(), l.end(), 7);
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Accumulate the values in a container

What are the requirements on the types?
```c++
template <typename Iterator, typename T>
T accumulate (Iterator first, Iterator last, T init);
```
- Iterator `first` must be *Incrementable*
- Iterator `first` must be *Dereferenceable*
- `first` and `last` must be *Comparable*
- Only a single-pass through all the elements required
- The dereferenced iterator `*first` must be *Addable* to an object of type `T`

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Accumulate the values in a container

With constraints:

```c++
template <std::forward_iterator Iterator, typename T>
T accumulate (Iterator first, Iterator last, T init);
```

--

Maybe better two distinct types:
```c++
template <std::input_iterator I, std::sentinel_for<I> S, typename T>
T accumulate (I first, S last, T init);
```
with [`std::sentinel_for`](https://en.cppreference.com/w/cpp/iterator/sentinel_for) essentially
means an Iterator that can be compared to its template parameter.


---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Copy from one into another container
```c++
template <typename InputIt, class OutputIt>
OutputIt copy (InputIt first, InputIt last, OutputIt d_first)
{
  while (first != last)
    *d_first++ = *first++;
  return d_first;
}
```

--

or with constraint template parameters:
```c++
template <std::input_iterator I, std::sentinel_for<I> S, typename O>
OutputIt copy (I first, S last, O d_first)
{
  while (first != last)
    *d_first++ = *first++;
  return d_first;
}
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Copy from one into another container
```c++
template <typename InputIt, class OutputIt>
OutputIt copy (InputIt first, InputIt last, OutputIt d_first)
{
  while (first != last)
    *d_first++ = *first++;
  return d_first;
}
```

or with constraint template parameters (advanced), see [ranges/copy](https://en.cppreference.com/w/cpp/algorithm/ranges/copy):
```c++
template <std::input_iterator I, std::sentinel_for<I> S, std::weakly_incrementable O>
  requires std::indirectly_copyable<I, O>
OutputIt copy (I first, S last, O d_first)
{
  while (first != last)
    *d_first++ = *first++;
  return d_first;
}
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: Copy from one into another container
Copy the elements between arbitrary containers
```c++
std::list<int> l{9,8,7,6,5,4};
std::vector<int> v(l.size());  // vector must have correct size
std::copy(l.begin(), l.end(), v.begin());

std::vector<int> v_out;       // empty vector
std::copy(l.begin(), l.end(), std::back_inserter(v_out));
```

With `auto bi = std::back_inserter(<container>)` a special output iterator that calls `push_back()` each time the
dereferenced iterator gets something assigned:
```c++
*bi = value; // effect: <container>.push_back(value)
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: `std::lower_bound` and `std::upper_bound`

```c++
// Return iterator to first element >= value, or last
template <class ForwardIt, class T>
ForwardIt lower_bound (ForwardIt first, ForwardIt last, const T& value);
// Return iterator to first element > value, or last
template <class ForwardIt, class T>
ForwardIt upper_bound (ForwardIt first, ForwardIt last, const T& value);
```

Example
```c++
#include <algorithm>
#include <vector>
int main() {
  std::vector<int> v = {1, 2, 2, 3, 3, 3, 4};
  auto res_it1 = std::lower_bound(v.begin(), v.end(), 3);
  int a = std::distance(v.begin(), res_it1); // 3
  auto res_it2 = std::lower_bound(v.begin(), v.end(), 0);
  int b = std::distance(v.begin(), res_it2); // 0
}
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: `std::fill`

The algorithm `std::fill` sets all elements of a range to the same value:
```c++
// #include <algorithm>
template <class ForwardIt, class T>
void fill (ForwardIt first, ForwardIt lst, T const& value)
{
  for (; for != last; ++first)
    *first = value;
}
```

---

# The C++ Standard Library
## Algorithms with Iterators
### Example: `std::iota`

The algorithm `std::iota` fills a sequence with increasing values, starting from an initial value:
```c++
// #include <numeric>
template <class ForwardIt, class T>
void iota (ForwardIt first, ForwardIt lst, T value)
{
  while (first != last) {
    *first++ = value;
    ++value;
  }
}
```