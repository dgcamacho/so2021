---
class: center, middle
# Constraints and concepts
---

# Constraints and concepts
- Not all algorithms can be specialized with types
- Sometimes we need type *categories*, type *properties*, or type *concepts*

## Example - Euclidean distance
```c++
template <typename Point>
double distance (Point const& a, Point const& b) {
  double result = 0.0;
  for (std::size_t i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}
```


### Requirements
- `Point` must be array-like, i.e., `operator[](int)` and `size()` function
- value type of `Point` should be (convertible to) `double`

---

# Constraints and concepts
- **SFINAE trick:** Introduce a substitution failure for types that are not supported
- Can be done inside a `decltype(...)` trailing return-type:

## Example - Euclidean distance
```c++
template <typename Point>
auto distance (Point const& a, Point const& b)
  -> decltype((std::size_t(a.size()), double(a[0]))) // comma separated list of expression
{                                                    // last expression determines type
  double result = 0.0;
  for (std::size_t i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}
```

---

# Constraints and concepts
- **SFINAE trick:** Introduce a substitution failure for types that are not supported
- Can be done inside a `decltype(...)` trailing return-type:

## Example - Euclidean distance

```
error: no matching function for call to ‘distance(double, double)’
   23 |   distance(1.0,2.0);
      |                   ^
specialization.cc:5:6: note: candidate: ‘template<class Point> decltype (((std::size_t)(a.size()), (double)(a[0]))) distance(const Point&, const Point&)’
    5 | auto distance (Point const& a, Point const& b) -> decltype((std::size_t(a.size()), double(a[0]))) {
      |      ^~~~~~~~
specialization.cc:5:6: note:   template argument deduction/substitution failed:
specialization.cc: In substitution of ‘template<class Point> decltype (((std::size_t)(a.size()), (double)(a[0]))) distance(const Point&, const Point&) [with Point = double]’:
specialization.cc:23:19:   required from here
specialization.cc:5:75: error: request for member ‘size’ in ‘a’, which is of non-class type ‘const double’
    5 | auto distance (Point const& a, Point const& b) -> decltype((std::size_t(a.size()), double(a[0]))) {
      |                                                                         ~~^~~~
specialization.cc:5:92: error: subscripted value is neither array nor pointer
    5 | auto distance (Point const& a, Point const& b) -> decltype((std::size_t(a.size()), double(a[0]))) {
      |                                                                                           ~^
```

---

# Constraints and concepts
## Definitions
- Class templates, function templates, and non-template functions (typically members of class templates)
  may be associated with a **constraint**, which specifies the requirements on template arguments,
  which can be used to select the most appropriate function overloads and template specializations.
- A **concept** is a named set of requirements consisting of valid expressions, associated types, invariants, and complexity
guarantees.
- Each concept is a predicate, evaluated at compile time, and becomes a part of the interface of a
  template where it is used as a constraint.
- A type that satisfies the requirements is said to **model** the concept, or be a model of the concept.
- A concept can extend the requirements of another concept, which is called **refinement**.


---

# Constraints and concepts
## Valid Expressions

C++ expressions which must compile successfully for the objects involved in the expression to be
considered models of the concept, e.g.,

.font-md[
<table width="100%" border="1">
<thead>
<tr><th>Name</th><th>Expression</th><th>Pre-Cond. </th><th>Semantics</th><th>Post-cond.</th></tr>
</thead>
<tbody>
<tr>
  <td>Size</td>
  <td><code class="remark-inline-code">a.size()</code></td>
  <td></td>
  <td>Returns the size of the container, that is, its number of elements.</td>
  <td><code class="remark-inline-code">a.size() >= 0 && a.size() <= MAX SIZE</td>
</tr>
<tr>
  <td>Element access</td>
  <td><code class="remark-inline-code">a[n]</code></td>
  <td><code class="remark-inline-code">0 <= n < a.size()</code></td>
  <td>Returns the nth element from the beginning of the container.</td>
  <td></td>
</tr>
</tbody>
</table>
]

---

# Constraints and concepts
## Associated Types

Types that are related to the modelling type in that they participate in one or more of
the valid expressions. Typically associated types can be accessed either through `using` or `typedef` nested
within a class definition for the modelling type, or they are accessed through a *traits class*, e.g.,

.font-md[
<table width="100%" border="1">
<thead>
<tr><th>Name</th><th>Expression</th><th>Semantics</th></tr>
</thead>
<tbody>
<tr>
  <td>Value type</td>
  <td><code class="remark-inline-code">X::value_type</code></td>
  <td>The type of the object stored in a container. The value type must be <i>Assignable</i>, but need not be <i>DefaultConstructible</i>.</td>
</tr>
</tbody>
</table>
]


---

# Constraints and concepts
## Invariants

Run-time characteristics of the objects that must always be true, that is, the functions involving
the objects must preserve these characteristics. The invariants often take the form of pre-conditions and
post-conditions, e.g. a class that implements a monoid operation must satisfy:

.font-md[
<table width="100%" border="1">
<thead>
<tr><th>Name</th><th>Semantics</th></tr>
</thead>
<tbody>
<tr>
  <td>Associativity</td>
  <td>For any <code class="remark-inline-code">x</code>, <code class="remark-inline-code">y</code>, and
      <code class="remark-inline-code">z</code>, <code class="remark-inline-code">f(x, f(y, z))</code> and
      <code class="remark-inline-code">f(f(x, y), z)</code> return the same value.</td>
</tr>
</tbody>
</table>
]

---

# Constraints and concepts
## Complexity Guarantees

Maximum limits on how long the execution of one of the valid expressions will take,
or how much of various resources its computation will use, e.g.,

.font-md[
<table width="100%" border="1">
<thead>
<tr><th>Semantics</th></tr>
</thead>
<tbody>
<tr>
  <td>The run-time complexity of element access is amortized constant time.</td>
</tr>
</tbody>
</table>
]

---

# Constraints and concepts
## Concepts
A concept is a named set of requirements. The definition of a concept must appear at namespace scope.

The definition of a concept has the form
```c++
template <template_parameter_list>
concept concept_name = constraint_expression;
```

---

# Constraints and concepts
## Constraints
A constraint is a sequence of logical operations and operands that specifies requirements on template
arguments. They can appear within *requires-expressions* and directly as bodies of concepts.

There are three types of constraints:
1. conjunctions (combination of constraints using `&&`)
2. disjunctions (combination of constraints using `||`)
3. atomic constraints

---

# Constraints and concepts
## Requires clauses

The keyword `requires` is used to introduce a **requires-clause**, which specifies constraints on
template arguments or on a function declaration.

```c++
template <typename T>
void f (T&&) requires Concept<T>; // can appear as the last element of a function declarator

template<typename T> requires Addable<T> // or right after a template parameter list
T add (T a, T b) { return a + b; }
```

In this case, the keyword `requires` must be followed by some constant expression (so it's possible
to write `requires true`), but the intent is that a named concept (as in the example above) or a
conjunction/disjunction of named concepts or a *requires-expression* is used.

---

# Constraints and concepts
## Requires expressions

The keyword `requires` is also used to begin a **requires-expression**, which
is an expression of type `bool` that describes the constraints on some template arguments. Such an
expression is `true` if the constraints are satisfied, and `false` otherwise:

```c++
template <typename T>
concept Addable = requires (T x) { x + x; };  // requires-expression

template <typename T> requires Addable<T>     // requires-clause, not requires-expression
T add(T a, T b) { return a + b; }

template <typename T>
  requires requires (T x) { x + x; }          // ad-hoc constraint, note keyword used twice
T add(T a, T b) { return a + b; }
```

---

# Constraints and concepts
## Requires expressions
The syntax of requires-expression is as follows:
```c++
requires ( parameter_list (optional) ) { requirement_seq };
```
- `parameter_list`	a comma-separated list of parameters like in a function declaration. These
parameters are only used to assist in specifying requirements. (optional)
- `requirement_seq` a	sequence of requirements, described below (each requirement ends with a semicolon).

--

Each requirement in the `requirements_seq` is one of the following:
- simple requirement (arbitrary expression statement)
- type requirements (the keyword `typename` followed by a type name)
- nested requirements (the keyword `requires` followed by a *constraint_expression*)
- compound requirements (syntax: `{ expression } -> type_constraint`)

---

# Constraints and concepts
## Requires expressions - Examples

### The array-like Concept
```c++
template <class A>
concept Array = requires (A a, typename A::size_type i) {
  { a.size() } -> std::integral;                                // compound requirement
  { a[i] }     -> std::convertible_to<typename A::value_type>;  // implicit type req.
};
```

### An Arithmetic Concept
```c++
template <class T>
concept Arithmetic = requires (T a, T b) {
  a + b;                            // simple requirement
  a - b;
  -a;
  requires std::totally_ordered<T>; // nested requirement
};
```
Additional invariants: `(a + b) + c == a + (b + c)`

---

# Constraints and concepts
## Function overloading based on ordering of constraints

- If concept `A` refines concept `B`, then `A` is more specialized
- In an overload resolution, the most specialized (and most constraint) function that fulfils
  the requirements is selected

```c++
template <Array Point>              // constraint: `Point` must be model of `Array`
auto distance (Point const& a, Point const& b) {  // (a)
  typename Point::value_type result = 0.0;
  for (typename Point::size_type i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}

template <class T>
  requires Arithmetic<T>            // requires-clause
T distance (T const& a, T const& b) {             // (b)
  return std::abs(a - b);
}
```

---

# Constraints and concepts
## Function overloading based on ordering of constraints

- If concept `A` refines concept `B`, then `A` is more specialized
- In an overload resolution, the most specialized (and most constraint) function that fulfils
  the requirements is selected

```c++
template <Arithmetic T>
  requires std::unsigned_integral<T>  // concept refinement
T distance (T const& a, T const& b) {             // (c)
  return a > b ? a - b : b - a;
}

int main() {
  using Point = std::array<double,2>;
  Point a{1.0,2.0}, b{2.0,3.0};

  auto d1 = distance(a, b);       // (a)
  auto d2 = distance(1.0,2.0);    // (b)
  auto d3 = distance(1.0f,2.0f);  // (b)
  auto d4 = distance(1u,2u);      // (c)
}
```