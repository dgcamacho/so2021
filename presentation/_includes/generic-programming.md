---
class: center, middle
# Generic Programming
---

# Generic Programming

Recall the example from the function section:

```c++
int     square (int const    x) { return x*x; }
float   square (float const  x) { return x*x; }
double  square (double const x) { return x*x; }
```

- Functions implementing the same algorithm should have the same name!
- Same algorithm contains same code - repetition
- General principle DRY: **Don't repeat yourself**

--

- Parametrize function with types (and values) \(\to\) template of a function

```c++
template <typename T>
T square (T const x) { return x*x; }
```

---

# Generic Programming
## Function Templates
- Instead of functions with explicit argument types, add (named) placeholder type,
  called *template parameters*
- Template parameters introduced with `class` or `typename`

```c++
template <typename T1, typename T2...>
<return_type> <function_name> (<args>...);
```

--

- Function arguments and function body can use placeholder types like any other
  specific type.

---

# Generic Programming
## Function Templates - Instantiation
- Templates are not real functions! They must be *instantiated* with concrete types.
- Template instiation either explicitly by `function_name<T1,T2>(<args>...)`
  or implicitly by "pattern matching" if argument list depends on all the types
  `T1,T2...`

```c++
int main() {
  square<int>(42);  // explicit template instantiation
  square<>(21);     // implicit instantiation -> T = int
  square(7);        // implicit instantiation -> T = int
}
```

- Implicit instantiation with angular brackets `<>`enforces a template instantiation
- Implicit instantation is called *argument type deduction* (ATD)

---

# Generic Programming
## Function Templates
- For multiple template parameters mixed explicit-implicit instantiation possible:
  Specify types explicitly in order (from left to right), all non-specified types must
  be deducible
- Template parameter can have *default values* (like for function parameters)

```c++
template <typename T1, typename T2, typename T3 = bool>
void template_function (T2 arg)
{
  T1 var1 = 7;    // use template parameters like real types
  T2 var2 = arg;
  T3 var3 = true;
}
...
template_function<double>(21);  // T1 = double, T2 = int, T3 = bool
```

---

# Generic Programming
## Function Templates
- If the type of the arguments is not explicitly needed, use *abbreviated function templates*, i.e.,
  simple placeholder argument type `auto`

```c++
auto square (auto const x) { return x*x; }    // [C++20]
...
square(42);   // x has type int const
```

---

# Generic Programming
## Function Templates
### Constrained Template Parameters
- Since C++20 the possible types of a function template can be constrained
- Remember section about *Constrained Placeholders*
- Replace `auto` by `<type_constraint> auto`

```c++
auto square (std::floating_point auto const x) { return x*x; }

// function overload with different type constraint
auto square (std::integral auto const x) { return x*x; }
```

--

- Also possible for named template parameters, replace `typename T` by `<type_constraint> T`

```c++
template <std::floating_point T>
auto square (T const x) { return x*x; }
```

---

# Generic Programming
## Function Templates
### Function overloading
- Overloading means: use the same name for functions with different *signature*
- Function templates have an extended signature, that includes the template
  parameter list (number of parameters, type-constraints, data-type or value-type parameter)
- Also included in the signature is the scope (namespace scope / class scope)

--

### Overload resolution - Which function is called?
1. Find possible candidate functions with the correct name
2. Argument type deduction for templates
3. Remove function that do not fit (e.g. wrong number of arguments)
4. Find best fitting function / most specialized/constrained function

---

# Generic Programming
## Function Templates
### Example

```c++
template <class T> // alternative syntax
T square (T const x) { return x*x; }        // (1)

// non-template function
int square (int const x) { return x*x; }    // (2)
```

--

### 1. Pass `int` to function:

```c++
square(42);
```

- `(1)` and `(2)` are found overloads
- argument type deduction for `(1)` results in `int`
- non-template function preferred over template function \(\to\) `(2)`

---

# Generic Programming
## Function Templates
### Example

```c++
template <class T> // alternative syntax
T square (T const x) { return x*x; }        // (1)

// non-template function
int square (int const x) { return x*x; }    // (2)
```


### 2. Pass `double` to function:

```c++
square(42.0);
```

- `(1)` and `(2)` are found overloads
- argument type deduction for `(1)` results in `double`
- non-template function is not an *exact match*, i.e., need type conversion.
- template function with `T=double` is better match \(\to\) `(1)`

---

# Generic Programming
## Function Templates

Since function template are generated at compile
time, the full specification, i.e., function header and body, has to be
available whenever such a function is used. Therefore, template
functions must always be implemented in a **header file**.

> .h3[Remark:] If many template functions are used for many different
> datatypes, this significantly can bloat the resulting compiled
> program. Also, the compilation time can be much higher.

---

# Generic Programming
## Function Templates

If you want to split declaration and definition of a template function,
both parts must be put into a header file.

### Example
```c++
#pragma once

// declaration of the function template
template <class T>
T square (T const x);

// definition of the function template
template <class T>
T square (T const x) { return x*x; }
```

---

# Generic Programming
## Function Templates

If you want to split declaration and definition of a template function,
both parts must be put into a header file.

### Example
```c++
#pragma once
// square.hh: declaration of the function template
template <class T>
T square (T const x);

#include "square.impl.hh" // include at the end of the file
```

Implementation file:
```c++
#pragma once
// square.impl.hh: definition of the function template
template <class T>
T square (T const x) { return x*x; }
```

---

# Generic Programming
## Class Templates
Similar to function templates, one can parametrize classes/structs with type parameters:
```c++
template <typename T1, typename T2...>
class <class_name>
{
  // examples of using the template types
  using value_type = T1;
  T1 var1;
  void fun (T2 arg) { ... };
};
```

### Example for a simple list:
```c++
template <typename T>
struct List {
  T element;
  List* next;
};
```

---

# Generic Programming
## Class Templates - Instantiation
Class templates are instantiated similar to function templates

1. Explicit instantiation by specifying the types
2. Implicit instantiation by *class template argument deduction* (CTAD)

### 1. Explicit instantiation

```c++
int main ()
{
  List<int> ilist;
  List<double>* dlist = new List<double>;

  ilist.element = 2;
  ilist.next = nullptr;

  dlist->element = 2.0;
  dlist->next = nullptr;
}
```


---

# Generic Programming
## Class Templates - Instantiation
Class templates are instantiated similar to function templates

1. Explicit instantiation by specifying the types
2. Implicit instantiation by *class template argument deduction* (CTAD)

### 2. Implicit instantiation

```c++
template <class T>
struct Wrapper
{
  T const& ref_;
  // constructor depends on T
  explicit Wrapper (T const& ref) : ref_(ref) {}
};

int main () {
  int var = 7;
  Wrapper w{var};   // deduction of type T from constructor function
}
```

---

# Generic Programming
## Class Templates - Deduction guides
If the constructor does not directly depend on the template parameters, or is itself a template
one can write *deduction guides* to tell the compiler how to deduce the template parameters:

The constructor is thereby written as a template function with trailing return type:
```c++
template <class T1...>
struct class_name
{
  class_name (<args>...);
};

// deduction guide
template <class T1...>
class_name (<args>...) -> class_name<S1,...>
```

---

# Generic Programming
## Class Templates - Deduction guides
### Example
```c++
template <class T, class Dummy>
struct Wrapper
{
  T const& ref_;
  // constructor depends on T
  explicit Wrapper (T const& ref) : ref_(ref) {}
};
```
Parameter `Dummy` cannot be deduced automatically.

Deduction Guide:
```c++
template <class T>
Wrapper (T const&) -> Wrapper<T, void>;
```

---

# Generic Programming
## Class Templates - Nested Templates
The template parameter can be any concrete type. After instantiation, a class template gets a concrete
type. Thus it can be used inside templates:

```c++
int main ()
{
  List< List<float> >  fllist;

  fllist.element.element = 2.0f;
  fllist.element.next    = nullptr;
  fllist.next            = nullptr;
}
```

Here, the list can be extended in two dimensions, either by the
`next` pointer or the `element.next` pointer.

---

# Generic Programming
## Function Templates and Class Templates
Function templates and class templates can be combined. When declaring a function template, the
arguments can be class templates or qualified types

```c++
template <class T>
double norm1 (std::vector<T> const& vec); // accept all std::vector arguments only

template <class T>
double norm2 (T const& arg); // accept any type and pass it by reference

template <class T>
double norm3 (T const arg); // accept any type and pass it by value
```
The parameter `T` is deduced depending on how it is called:
```c++
std::vector vec{1.0, 2.0, 3.0}; // NOTE: CTAD happens here

norm1(vec); // => T = double
norm2(vec); // => T = std::vector<double>
norm3(vec); // => T = std::vector<double>
```

---

# Generic Programming
## Alias Templates

We have seen *alias types* or *typedefs* before. These can also be templated:
```c++
template <typename T1, typename T2...>
using <alias> = class_name<T1,T2...>;
```

--

## Dependent Names
Classes can have associated types as components. but also static functions, static members and a lot more.
When accessing associated types of a template parameter, we have to give the compiler a hint what we want
with the keyword `typename`:

```c++
template <class T>
struct Wrapper
{
  using value_type = typename T::value_type; // `T::value_type` is dependent on `T`
};
```

---

# Generic Programming
## Alias Templates and Dependent Name

Alias templates are sometimes used to access common dependent types. The additional `typename` can
thereby be hidden in the alias:

```c++
template <class Container>
using value_t = typename Container::value_type;
```

--

On the other hand, if an alias template is part of a class, we might need to use an additional keyword
`template` to access these types:

```c++
struct Wrapper {
  template <class T>
  using type = T;
};

template <class T, class W>
auto foo (W const& wrapper) -> typename W::template type<T> {
  return T(1);
}
```

---

# Generic Programming - Example: CG Method
```c++
template <class Mat, class Vec, class Iteration>
int cg (Mat const& A, Vec& x, Vec const& b, Iteration& iter)
{
  using Scalar = typename Vec::value_type;

  Scalar rho{0}, rho_1{0}, alpha{0};
  Vec p{b}, q{b}, z{b};
  Vec r{b};
  A.mv(-1.0, x, r);                             // r = b - A*x

  rho = r.dot(r);                               // rho = r^T * r
  while (! iter.finished(std::sqrt(rho))) {  ++iter;
    if (iter.first())  p = r;
    else               p.aypx(rho / rho_1, r);  // p = r + (rho / rho_1) * p;
    A.mv(p, q);                                 // q = A * p
    alpha = rho / p.dot(q);                     // alpha = rho / (p^T * q)
    x.axpy(alpha, p);                           // x += alpha * p
    r.axpy(-alpha, q);                          // r -= alpha * q
    rho_1 = rho;                                // rho_1 = rho
    rho = r.dot(r);                             // rho = r^T * r
  }
  return iter;
}
```

---

# Generic Programming
## Non-Type Template Parameter
Apart from type parameters, template parameters can represent (integral) values. Instead of
specifying the template parameter with `typename` or `class`, it is declared with a corresponding
data type, e.g. `int`.

```c++
template <class T, int N>
struct fixed_size_array
{
  T& operator[](int i) { return data[i]; }
  const T& operator[](int i) const { return data[i]; }

  T data[N];  // size is fixed by template parameter
};

int main()
{
  fixed_size_array<double, 3> point3D;
  point3D[2] = 7.0;
}
```

---

# Generic Programming
## Non-Type Template Parameter

- Not all types are allowed as non-type template parameters.
- It must be possible to uniquely evaluate those types at compile-type. Therefore the C++
  standard has restricted non-type template parameters to so-called *structural types*, e.g.,

  * integral types, enums, characters, and pointer types.
  * `std::nullptr_t`
  * floating-point type [C++20]
  * *literal* class type [C++20] (only `public` + `const` structural type members)

- You can specify the `auto` placeholder if you do not want to be too specific:

```c++
template <class T, auto N>
struct fixed_size_array;
```

---

# Generic Programming
## Non-Type Template Parameter

- Not all types are allowed as non-type template parameters.
- It must be possible to uniquely evaluate those types at compile-type. Therefore the C++
  standard has restricted non-type template parameters to so-called *structural types*, e.g.,

  * integral types, enums, characters, and pointer types.
  * `std::nullptr_t`
  * floating-point type [C++20]
  * *literal* class type [C++20] (only `public` + `const` structural type members)

- You can specify the `auto` placeholder if you do not want to be too specific:

```c++
template <class T, std::integral auto N> // or even with constraints
struct fixed_size_array;
```