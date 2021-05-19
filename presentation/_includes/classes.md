---
class: center, middle
# Classes
---

# Classes
## Structs with Member Functions
Structs were previously introduced only as a way to group data. In C++, structs can also be
associated with functions. Those are called *member functions* or *methods* of the struct.

```c++
struct Vector {
    std::size_t  size;
    real_t*      data;

    void init  (std::size_t n);
    void set   (real_t value);
    void scale (real_t factor);
};
```

For the implementation of these functions, their name is prefixed by the struct name:

```c++
void Vector::init (std::size_t const n);
{
  ...
}
```

---

# Classes
## Structs with Member Functions
A member function is called specifically for an **instance** of a struct, using the same dot operator
`.` (or `->` pointer access operator) as for struct variables:

```c++
int main ()
{
  Vector x;

  x.init(10);
  x.set(1.0);
  x.scale(5.0);

  return 0;
}
```

---

# Classes
## Member Function Implementation
Inside a member function, one has implicit access to all data members of the specific struct object,
for which the function was called. Therefore, the following two
functions are equivalent:


.pure-g[.pure-u-1-2[.padding-5[
```c++
void Vector::init (std::size_t const n)
{
  size = n;
  data = new real_t[n];
}
...
Vector x;
x.init(10);
```
]].pure-u-1-2[.padding-5[
```c++
void init (Vector& x, std::size_t const n)
{
  x.size = n;
  x.data = new real_t[n];
}
...
Vector x;
init(x, 10);
```
]]]

---

# Classes
## Member Function Implementation
A **pointer** to the corresponding struct object is actually available in C++. It is called
`this`. Hence, one can also write:

```c++
void Vector::init (std::size_t const n)
{
  this->size = n;
  this->data = new real_t[n];
}
```

---

# Classes
## Member Function Implementation

Struct member functions can also be *implemented* in the definition of the `struct`. They are
then automatically declared as `inline` functions:

```c++
struct Vector {
  ...
  void init (std::size_t const n)   // inline function
  {
    size = n;
    data = new real_t[n];
  }
  ...
};
```

> .h3[Remark:] Inline definitions of struct members should be restricted to simple/short functions.
> The non-inline definitions are typically put into a separate source file, whereas the struct
> definition including the member function *declarations* are put into a header file.

---

# Classes
## `const` Member Functions
Member functions not changing the struct data should be defined as `const` functions:

```c++
struct Vector {
  ...
  void   scale (real_t const factor); // modifies the data
  real_t two_norm () const;           // just reads the values
  ...
};
```

When calling member functions for `const` objects, e.g.,

```c++
Vector x; // init x...
Vector const& y = x;
```

only such `const` functions are allowed to be called, since all non-`const`
functions potentially *change* the object:

```c++
std::cout << y.two_norm() << std::endl;  // Ok: Vector::two_norm is const
y.scale(2);                              // ERROR: Vector::scale is non-const
```

---

# Classes
## Constructors and Destructor
There are special functions for each struct:

**Constructors**
:   functions automatically called when a struct type is instantiated,
    e.g., by `new` or stack allocation, and

**Destructor**
:   a function automatically called when a struct variable is destroyed,
    e.g., by `delete` or if it goes out of scope.

--

The name of a constructor function is identical to the name of the
struct, whereas the name of the destructor is the struct name prefixed by `~`:

```c++
struct Vector {
  ...
  Vector  ();                     // constructor 1
  Vector  (std::size_t const n);  // constructor 2
  ~Vector ();                     // destructor
};
```

---

# Classes
## Constructors and Destructor
By definition, constructors should create necessary resources for the object, whereas destructors
should free all struct object resources:

.pure-g[.pure-u-2-3[.padding-5[
```c++
Vector::Vector ()   // default constructor
{
  size = 0;
  data = nullptr;
}
// Constructor with parameter
Vector::Vector (std::size_t const n)
{
  size = n;
  data = new real_t[n];
}
```
]].pure-u-1-3[.padding-5[
```c++
Vector::~Vector ()
{
  delete[] data;
}
```
]]]


> .h3[Remark:] Constructors and the destructor have no return type. Furthermore,
> destructors must not have function arguments.

---

# Classes
## Constructors and Destructor - Example 1
Structs can be instantiated and destroyed explicitly by `new` and `delete`:

```c++
Vector* x = new Vector{};     // calling constructor 1
Vector* y = new Vector{10};   // calling constructor 2

y->set(1.0);

delete x;                     // calling destructor
delete y;                     // calling destructor
```

> .h3[Remark:] If the constructor has no arguments, the corresponding parentheses can
> be omitted. But, prefer universal initialization with `{}`

```c++
Vector* x = new Vector;         // calling constructor 1
```

---

# Classes
## Constructors and Destructor - Example 2
Structs can be  instantiated and destroyed implicitly by block scope:

```c++
{
  Vector  x{};     // calling constructor 1
  Vector  y{10};   // calling constructor 2

  y.set(1.0);
}                  // destructor for x and y called automatically
```

Here, the struct objects are not pointers. When leaving the block, the destructors of **all**
struct objects are called *automatically*! Thereby, it is ensured, that all resources are
released.

---

# Classes
## RAII

**Resource acquisition is initialization** (RAII) means resource allocation (or acquisition)
is done during object creation (specifically initialization), by the **constructor**, while resource
deallocation (release) is done during object destruction (specifically finalization), by the
**destructor**. The resource is guaranteed to be held between when initialization finishes and
finalization starts, and to be held only when the object is alive.

Resources can be, for example,
- Memory that is allocated and deallocated
- A file that is opened and closed
- Thread *lock* that is acquired and released

---

# Classes
## Special Constructors
By default, each struct type has some constructors already implemented by the C++ compiler: e.g., the
**default** constructor and the **copy** constructor.

The default constructor is a constructor *without* arguments, e.g., `constructor 1` in the previous
example. The copy constructor is a constructor with one argument being a `const&` to an
object of the same type as the struct itself:

```c++
struct Vector {
    ...
    Vector (Vector const& that);  // copy constructor
};
```

This is used for

```c++
Vector  x{10};
Vector  y{x};     // call copy constructor
Vector  z = x;    // usually converted into z{x}
```

---

# Classes
## Special Constructors - Default Behavior
The default constructor implemented by the C++ compiler **does nothing**, i.e., it does not
initialize the member variables.

The C++ generated copy constructor simply copies the data in each
member variable of the record:

```c++
Vector* x = new Vector{10};
Vector* y = new Vector{*x};  // now: x.data == y.data,
                              // e.g. equal pointers
```

Here, changing `y` also changes `x`:

```c++
x->data[ 5 ] = 2;   // also changes y.data[ 2 ]
y->data[ 3 ] = 4;   // also changes x.data[ 3 ]
```

---

# Classes
## Special Constructors - Copy Constructor
For vectors, instead of the pointers, the content of the array should be copied:

```c++
Vector::Vector (Vector const& that)
{
  size = that.size;
  data = new real_t[size];

  for (std::size_t i = 0; i < size; ++i)   // deep copy
    data[i] = that.data[i];
}
```

Now, the instructions

```c++
Vector* x = new Vector{10};
Vector* y = new Vector{*x};

x->data[ 5 ] = 2;
y->data[ 3 ] = 4;
```

only effect either `x` or `y`, not both.

---

# Classes
## Visibility
All member variables and functions of a struct were visible and accessible from any other function
or datatype in C++. This makes illegal changes to the data in a struct possible, e.g., change
the `size` variable of `Vector` without also changing the `data` variable.

To prevent this behavior, one can change the visibility of variables and
functions using one of the following keywords:

`public`
:   variables or functions can be accessed without restrictions,

`protected`
:   variables or functions can only be accessed by member functions of
    the struct type or by derived structs (see later),

`private`
:   variables or functions can only be accessed by member functions of
    the struct type.

---

# Classes
## Visibility - Example 1:

```c++
struct Vector {
private:                // all following variables and functions
    std::size_t size_;  // are private
    real_t*     data_;

public:                // all following variables and functions
                       // are public
    Vector (std::size_t const n);
...
    std::size_t size () const { return size_; }
};

...

{
  Vector  x{10};

  std::cout << x.size_ << std::endl;   // ERROR: size member is private
  std::cout << x.size() << std::endl;  // OK: size() member function is public
}
```

---

# Classes
## Encapsulation

- Bundling of data with the methods that operate on that data is referred to as **encapsulation**.
- Another aspect of *encapsulation* is the restricting of direct access to some of an object's components.

> .h3[Coding Principle:] Make **all** member variables of a struct `private` by default and allow
> read-/write-access only via member functions.

--

## `struct` vs `class`
In C++ another type of struct is available: `class`. The difference is that in a `class` all members
are `private` by default.

---

# Classes
## Encapsulation - Getter and Setter
The access to data members, e.g., `data`, is typically implemented either as

**Getter** and **Setter**
: Member function called `get_data()` or `getData()` returning `data` by value or `const&` and a
  second function called `void set_data(value)` or `void setData(value)` for setting the value of
  the data member.

```c++
class Wrapper
{
    double value;

public:
    double get_value () const   { return value; }
    void   set_value (double v) { value = v; }
};
```

---

# Classes
## Encapsulation - Getter and Setter
The access to data members, e.g., `data`, is typically implemented either as

**Direct access functions**
: A function with the same name as the data member can be written with two overloads for const and
  non-const access. Since this is not directly allowed, typically the data member is renamed, either
  `m_data`, `_data` or `data_` and the access function is called `data()`.

```c++
class Wrapper
{
    double value_;

public:
    double  value () const { return value_; }
    double& value ()       { return value_; }
};
```

---

# Classes
## Operator Overloading
In C++, operators, e.g., `+`, `*`, `=`, or `[.]`, can be defined for class
data types to simplify access or to ensure correct behavior.
Depending on the operator, it can be defined *inside* or *outside* the class definition, i.e.,
operators changing the object like `=` or `+=` are defined inside the class and binary operators
working on two objects typically outside the class.

In terms of syntax, operator functions are treated like any other function. The name of the
operator is defined by

```c++
<return_type> operator <operator_symbol> (<argument_types>...)
```
e.g.
```c++
operator+
operator*
operator=
operator[]
```

---

# Classes
## Operator Overloading - Example

```c++
struct Vector {
  ...
  // provide index operator for vectors
  real_t  operator[] (std::size_t const i) const { return data_[i]; }
  real_t& operator[] (std::size_t const i)       { return data_[i]; } // overload

  // arithmetics
  Vector& operator+= (Vector const& other)
  {
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] += other.data_[i];           // can be accessed since same class type
    return *this;                           // return reference to itself to allow chaining
  }
  Vector& operator*= (real_t const factor)
  {
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] *= factor;
    return *this;
  }
};
```

---

# Classes
## Operator Overloading - Example

```c++
int main()
{
  Vector x{10};
  Vector y{10};

  x[0] = 1.0;           // mutable element access
  real_t data = x[0];   // const element access

  x += y;               // calls x.operator+(y)
  y *= 2.0;             // calls y.operator+=(2.0)
}
```

---

# Classes
## Operator Overloading
- Binary arithmetic operator return a new object containing the operation result. This can be expensive
  when used with large data types.

- Typically, binary arithmetic operators are implemented in terms of copy and compound assignment operator:

```c++
Vector operator+ (Vector const& v1, Vector const& v2)
{
  Vector tmp{v1};     // create a copy of v1
  return tmp += v2;   // apply the compound assignment operator
}                     // return value -> new temporary
```

---

# Classes
## Operator Overloading
- Binary arithmetic operator return a new object containing the operation result. This can be expensive
  when used with large data types.

- Typically, binary arithmetic operators are implemented in terms of copy and compound assignment operator:

```c++
Vector operator+ (Vector tmp, Vector const& v2) // perform copy already in function call
{
  return tmp += v2;   // apply the compound assignment operator
}
```

--

> .h3[Remark:] The compile may perform return-value optimization (copy elision).

---

# Classes
## Special Operators
The analogy to the copy constructor there is the **copy-assignment operator** `=`, used in

```c++
x = y;
```

It is also generated by the C++ compiler by default, simply copying
the individual member variables of the class. Thereby, the same
problems occur, e.g., copying pointers instead of arrays.

> .h3[Coding Principle:] Always make sure, that the C++ generated copy constructor and
> copy-assignment operator behaves as expected. If you implement one of these, you need to
> implement also the other one.

---

# Classes
## Special Operators - Copy operator for vectors:

```c++
class Vector {
  ...
  Vector&  operator= (Vector const& that)
  {
    if (this != &that) {          // prevent from self assignment
      delete[] data_;             // delete the old data first

      size_ = that.size_;
      data_ = new real_t[size_];  // allocate new data

      // copy the data
      for (std::size_t i = 0; i < size_; ++i)
        data_[i] = that.data_[i];
    }
    return *this;
  }
};
```

Now, when assigning class objects to each other, e.g. `x = y`, the user-implemented copy-assignment
operator is used, ensuring correctness.

---

# Classes
## Special Operators
The copy-assignment operator also allows a simplified copy constructor:

```c++
Vector::Vector (Vector const& that)
{
  *this = that;
}
```

--

It is also possible to implement the copy-assignment operator in terms of the copy constructor
instead...

---

# Classes
## Special Operators
```c++
class Vector {
  ...
public:
  Vector (Vector const& that) {
    size_ = that.size_;
    data_ = new real_t[size_];  // allocate new data

    // copy the data
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] = that.data_[i];
  }
  Vector& operator= (Vector that) { // take the argument by copy (RAII)
    using std::swap;
    swap(size_, that.size_);   // swap the content of this and the temporary that
    swap(data_, that.data_);
    return *this;
  }
};
```
This is known as the **copy-and-swap ideom**.

---

# Classes
## Constructor Initializer Lists

- The initializer list specifies how member variables are initialized before the body of the constructor is executed
- Members should be initialized in the order of their definition
- Members are initialized to their default value if not specified in the list
- `const` member variables can only be initialized in the initializer list

Example
```c++
struct Vector {
  std::size_t size_;
  real_t* data_;

  Vector () : size_(0), data_(nullptr)
  {}
}
```

---

# Classes
## Constructor Initializer Lists

```c++
class <class_name> {
  <type1> <var1>;
  <type2> <var2>;
public:
  <class_name> (<argument_list>...) : <initializers>...
  {
    <body>
  }
};
```
where `<initializers>` is a comma separated list of initialization expressions, e.g., for a member variable `var` it could be something like `var{value}` or `var(value)` like the (universal) initializers of variables.

The initialization expressions might depend on the argument list of the constructor, but can also be explicit values.

---

# Classes
## Constructor Initializer Lists - Chaining Constructors

In initializer lists other constructors can be called. This allows to chain constructors. Other constructors have the name of the class that they are implemented in:

```c++
struct Vector {
  ...
  Vector (std::size_t const n = 0)  // (1)
    : size_(n), data_(n > 0 ? new real_t[n] : nullptr)
  {}

  Vector (Vector const& that)   // (2)
    : Vector(that.size_)        // calls (1)
  {
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] = that.data_[i];
  }
}
```

> .h3[Coding Principle:] Prefer initializer lists over initialization in the body.

---

# Classes
## Converting and Explicit Constructors
- Constructors with exactly one argument are treated specially: They are used for explicit and implicit conversions
- If implicit conversion with such constructors is not desired, the keyword `explicit` can be used to disallow it
- Generally, you should use `explicit` unless you have a good reason not to

.pure-g[.pure-u-1-2[.padding-5[
```c++
struct Vector {
  Vector (std::size_t const n);
};
// function accepting Vector by value
double norm(Vector v);
...
norm(10); // Implicit conversion,
  // calls Vector::Vector(std::size_t)

static_cast<Vector>(10); // OK
```
]].pure-u-1-2[.padding-5[
```c++
struct Vector {
  explicit Vector (std::size_t const n);
};
// function accepting Vector by value
double norm(Vector v);
...
norm(10); // ERROR: Implicit conversion


static_cast<Vector>(10); // OK
```
]]]

---

# Classes
## Application: BLAS (Version 3) Matrix type:

```c++
class DenseMatrix {
private:
    std::size_t rows_, cols_;
    real_t*     data_;

public:
    DenseMatrix (std::size_t const n, sd::size_t const m);
    DenseMatrix (DenseMatrix const& that);          // copy constructor
    ~DenseMatrix ();

    std::size_t rows () const;
    std::size_t cols () const;

    real_t  operator() (std::size_t const i, std::size_t const j) const;
    real_t& operator() (std::size_t const i, std::size_t const j);

    DenseMatrix& operator = (DenseMatrix const& that);  // copy-assignment operator
    DenseMatrix& operator = (real_t const value);       // set to value
    DenseMatrix& operator*= (real_t const factor);      // scale by factor

    void axpy (real_t const alpha, DenseMatrix const& X);
```

---

# Classes
## Application: BLAS (Version 3)

```c++
    void mv (real_t const alpha, Vector const& x, Vector& y) const;

    real_t frobenius_norm () const;
};

int main() {
  Matrix M{10, 10};
  Vector x{10};
  Vector y{10};

  x = 1.0;
  y = 0.0;

  ...
  M[3,4] = ... // fill matrix M

  std::cout << M.frobenius_norm() << std::endl;
  M.mv(-1.0, x, y); // y -= M*x
}
```
