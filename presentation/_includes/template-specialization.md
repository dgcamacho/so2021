---
class: center, middle
# Template Specialization
---

# Template Specialization
- Template introduce a way of programming that allows formulating algorithms independent of the
  concrete representation of data types
- Often (hidden) requirements are given for the template parameters
- Some types needs special treatment

## Example
Euclidean distance
```c++
template <typename Point>
double distance (Point const& a, Point const& b) { // primary template
  double result = 0.0;
  for (std::size_t i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}
```

---

# Template Specialization
- Template introduce a way of programming that allows formulating algorithms independent of the
  concrete representation of data types
- Often (hidden) requirements are given for the template parameters
- Some types needs special treatment

## Example
Euclidean distance of 1d points as floating-point numbers
```c++
template <> // Specialization for floating-point type double
double distance<double>(double const& a, double const& b) {
  return std::abs(a-b);
}
```

---

# Template Specialization
## Primary Template

> .h3[Definition:] The first complete (non-specialized) template definition is called the *primary
template*. It has a special meaning in the context of overload resolution.

## Specialization
- Always start with the keyword `template <...>`
- Specialized type(s) in angular brackets directly after the function name or class name

```c++
template <>
return_type function_name<Type1, Type2,...> (Arg1 arg1, Arg2 arg2...);

template <typename U1, typename U2,...>   // further template parameters allowed
class class_name<Type1, Type2,...>;       // Type1, Type2... might depend on U1, U2...
```

---

# Template Specialization
- The **primary template** specifies, that a function or class is a template. It is not specialized,
  but allows any template parameter. It is required to be declared (not necessarily defined)
  before any specialization.
- If no template parameters remain in the template parameter list, the specialization is called
  **full specialization**, otherwise **partial specialization**.

> .h3[Attention:] Partial template specialization is allowed *for class templates only*!

---

# Template Specialization
## Examples
```c++
// primary template
template <class T, class S>
class MyPoint; // Type T... element type, Type S... index type

// specialization for element type `double` and index type `int`
template <>
class MyPoint<double, int> { ... };           // (a)

// specialization for any element type but index type `long`
template <class T>
class MyPoint<T, long> { ... };               // (b)

// specialization for element type `MyPoint<T,int>' where `T` could be any type
// and fixed index type `int`
template <class T>
class MyPoint< MyPoint<T,int>, int > { ... }; // (c)
```

---

# Template Specialization
## Partial Template Specialization
- The specialized types depend on remaining template parameters
- Either the specialized type is equal to a template parameter or some qualification or might be
  part of another template

```c++
template <class ValueType>
struct Rational { ... };

// specialization for all matrices of type Matrix<T> where T is a free parameter
template <class T>
struct Rational<Matrix<T>> { ... };
```

---

# Template Specialization
## Partial Template Specialization
- Not allowed for function templates

```c++
// Declaration of the primary template
template <typename T, typename Index>
void foo ();

template <typename T>
void foo<T, int> () { ... }; // ERROR: Partial template specialization of function templates
```

--

- Need workaround with *tag dispatching*/additional function parameters...

```c++
// helper class template without any members and any data
template <typename T> struct id {};
```
Then `id<int>` and `id<T>` for any other `T` are distinct types
---

# Template Specialization
## Partial Template Specialization
- Not allowed for function templates

```c++
// dispatch function. Function parameter depending on the template parameters
template <typename T, typename Index>
void foo_impl (id<T>, id<Index>) { ... }  // (1)

// dispatch function for fixed `index` parameter'
template <typename T>
void foo_impl (id<T>, id<int>) { ... }    // (2)

// primary function template. Redirects to dispatch function
template <typename T, typename Index>
void foo () { foo_impl(id<T>{}, id<Index>{}); }
```
- In the code above, the dispatch function (2) is more constrained / more specialized than the general
  dispatch function (1).
- Both dispatch functions are primary templates here. No template specialization, but
  overloading for different template signatures.

---
class: center, middle
# Quiz
---

# Template Spacialization
## 1. Which function is called in `main()`?

```c++
template <class T> void foo(T);   /* (a) */
template <class T> void foo(T*);  /* (b) */
template <> void foo<int>(int*);  /* (c) */

int main() { int *p; foo(p); }
```

---

# Template Spacialization
## 2. Which function is called in `main()`?

```c++
template <class T> void foo(T);   /* (a) */
template <class T> void foo(T*);  /* (b) */
template <> void foo<int*>(int*); /* (c) */

int main() { int *p; foo(p); }
```

---

# Template Spacialization
## 3. Which function is called in `main()`?


```c++
template <class T> void foo(T);   /* (a) */
template <class T> void foo(T*);  /* (b) */
void foo(int*);                   /* (c) */

int main() { int *p; foo(p); }
```

---

# Template Spacialization
## Why Not Specialize Function Templates?

- Function template specialization makes the overload resolution complicated
- Might even depend on the order of declaration


> .h3[Guideline:] Do not mix template specialization and function overloading. Prefer function
> overloading in general.

---

# Template Spacialization
## Basic rules for overload resolution [[details](https://en.cppreference.com/w/cpp/language/overload_resolution)]
1) All visible names are collected (involving *argument dependent lookup* (ADL) in the
namespaces of the arguments)

2) All non-viable functions are erased from that list
  - Number of parameters must match (involving default function parameters)
  - There must be a sequence of implicit conversions to transform the passed arguments
    into the function parameter types.
  - For function templates all template parameters must be deducible (*argument type
    deduction* – ATD)
  - If the replacement of a template parameter by the type derived from ATD would
    lead to a direct error, this raises a *substitution failure*. Candidates involving a
    substitution failure are simply ignored (a *substitution failure is not an error* - SFINAE)

---

# Template Spacialization
## Basic rules for overload resolution [[details](https://en.cppreference.com/w/cpp/language/overload_resolution)]
3) A non-template function that is an exact match is the best fitting candidate.

4) For all primary template the most specialized one is selected.

5) If there are template specializations of the best fitting primary template, the most
   specialized (matching) one is selected.

--

## What does it mean to be the most specialized template?
For two function templates that one is more specialized whose arguments can be inserted into the
other function but not vice versa, e. g.,
```c++
template <class S> void foo (S);   // (1)
template <class T> void foo (T*);  // (2)
```
Every pointer `T*` is also an arbitrary (non-constrained) type `S`, but not all types `S` are pointer
types. Thus, (2) is more specialized than (1).

---

# Template Spacialization
## For functions prefer overloading!

### Example
```c++
template <typename Point>
double distance (Point const& a, Point const& b) {    // (a)
  double result = 0.0;
  for (std::size_t i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}

// function overloading:
double distance (double a, double b) {                // (b)
  return std::abs(a-b);
}
```

Problem: What if you want to call `distance()` with `float`?

--

**Answer:** `(a)` would be called, since `(b)` is not a perfect match \(\to\) error.
