---
class: center, middle
# Arrays and Dynamic Memory
---

# Arrays and Dynamic Memory
## Array Definition
So far, we had only datatypes with one entry per
variable. Arrays with a **fixed** number of entries are defined
as:

```c++
<type> <variable_name>[<number_of_entries>];
```

where the number of entries is an integral **constant** expression, e.g.,

```c++
int        n[ 5 ];
double     f[ 10 ];
const int  len = 32;
char       str[ len ];
```

--

Arrays can also be pre-initialized. In that case, the array size can be
omitted:

```c++
int  n1[6] = { 0, 1, 2, 3, 4, 5 };
int  n2[]  = { 3, 2, 1, 0 };          // automatically size of 4

auto n3[]  = { 3, 2, 1, 0 };          // ERROR: array of `auto` not allowed
auto n4    = { 3, 2, 1, 0 };          // OK, but std::initializer_list<int>, not array!!
```

---

# Arrays and Dynamic Memory
## Array Access
A single entry in an arrays is accessed by the element-access operator `[i]`:

```c++
double  f[5];

f[0]  = -1.0;
f[1]  =  3.0;
f[4]  =  f[1] * 42.0;

int i = 3;
f[i]  = f[0] + 8.0;
```

In C++, indices are counted from **zero**. The valid index range
is therefore:<br>`[0, ..., <array_size>-1]`

```c++
for (int i = 0; i < 5; ++i)
  f[i] = 2*i;
```

---

# Arrays and Dynamic Memory
## Array Access
There are normally no array boundary checks in C++. Accessing an array outside its valid index range
is **undefined behavior**.

### Typical error:

```c++
double  f[5];

for (int i = 0; i < 5; ++i)   // Ok
  f[i] = 2*i;

for (int i = 0; i <= 5; ++i)  // Bug
  f[i] = 2*i;
```

> .h3[Coding Principle:] Always make sure, that you access arrays within the valid index range.

---

# Arrays and Dynamic Memory
## Array Default Initialization
We have seen that arrays and be initialized with values using the brace-init list `{...}`. This
list can be shorter than the requested size of the array. The effect is, that all remaining entries
are initialized to zero:

```c++
int a1[5] = { 1, 2 };   // => {1, 2, 0, 0, 0}
int a2[5]{1,2,3};       // => {1, 2, 3, 0, 0}
```

This can even be used to initialize all entries of the array to zero:

```c++
int b1[5] = {};         // => {0, 0, 0, 0, 0}
int b2[5]{};            // => {0, 0, 0, 0, 0}
```

> .h3[Attention:] By default arrays are not initialized. You simply get the memory that is requested.

--

> .h3[Remark:] Only static arrays are initialized by default to zero.

---

# Arrays and Dynamic Memory
## Array Operations
Unfortunately, there are no operators for arrays, e.g., no assignment, elementwise addition or
multiplication like in other languages. All of these have to be programmed by yourself:

```c++
void copy (double const x[3], double y[3])
{
  for (int i = 0; i < 3; ++i)
    y[i] = x[i];
}
void add (double const x[3], double y[3])
{
  for (int i = 0; i < 3; ++i)
    y[i] += x[i];
}
```

> .h3[Remark:] Arrays can be used as function arguments like all basic datatypes. But
> *not* (directly) as function return types!

---

# Arrays and Dynamic Memory
## Multidimensional Arrays
So far, all arrays have been onedimensional. Multidimensional arrays are defined analogously
by appending the corresponding size per dimension:

```c++
int     mat[3][3];
double  tensor3[10][10][10];
long    tensor4[100][20][50];
```

The access to array elements in multidimensional arrays follows the same
pattern:

```c++
mat[0][0] =  1.0; mat[0][1] = 0.0; mat[0][2] = -2.0;
mat[1][0] =  0.0; mat[1][1] = 4.0; mat[1][2] =  1.0;
mat[2][0] = -2.0; mat[2][1] = 1.0; mat[2][2] = -1.5;

for (int i = 0; i < 100; ++i)
  for (int j = 0; j < 20; ++j)
    for (int k = 0; k < 50; ++k)
      tensor3[i][j][k] = double(i+j+k);  //< explicit cast
```

---

# Arrays and Dynamic Memory
## Multidimensional Array Initialization
Multidimensional arrays can be initialized by nested curly braces:

```c++
double mat1[2][3] = {
  {1.0, 2.0, 3.0},
  {4.0, 5.0, 6.0}
};

int mat2[][2] = { {1,2}, {3,4} };  // automatic size of inner dimensions
```

The initialization can also be provided as onedimensional list
```c++
int mat3[][2] = {1, 2, 3, 4} // similar to mat2
```

---

# Arrays and Dynamic Memory
## Multidimensional Arrays
### Example: Matrix-Vector multiplication

```c++
/// Matrix-vector product `y = mat * x`
void matvec (double const mat[3][3], double const x[3], double y[3])
{
  for (int i = 0; i < 3; ++i) {
    y[i] = 0.0;

    for (int j = 0; j < 3; ++j)
      y[i] += mat[i][j] * x[j];
  }
}
```

---

# Arrays and Dynamic Memory
## Size of an Array
While the syntax of declaring an array is simple and clean, we do not have intrinsic functions
to get the size of the array after declaration.

One solution is to use the `sizeof` operator + macros:
```c++
#define SIZE(a)  (sizeof(a) / sizeof(a[0]))
```

### Example:
```c++
int vec[5]{1,2,3};
static_assert(SIZE(vec) == 5);

// Problem:
void f (int vec[5]) {
  // warning: ‘sizeof’ on array function parameter ‘vec’ will return size of ‘int*’
  static_assert(SIZE(vec) == 5);  // ERROR
}
```

---

# Arrays and Dynamic Memory
## Size of an Array
While the syntax of declaring an array is simple and clean, we do not have intrinsic functions
to get the size of the array after declaration.

### Outlook: Templates
```c++
/// Return the number of entries in an array
template <class T, int N>
int array_size(T (&)[N]) { return N; }

/// Return the number of rows and columns in a matrix
template <class T, int N1, int N2>
std::pair<int,int> mult_array_size(T (&)[N1][N2]) { return {N1, N2}; }
```

> .h3[Remark:] The reference to an array is declared as <br>`<type> (&<ref_name>)[<size>] = <array>`

---

# Arrays and Dynamic Memory
## Arrays and Pointers
C++ does **not** support variable sized arrays as an intrinsic datatype.

Hence, arrays with an unknown size at compile time are not possible with
previous array types in C++.

But, in C++, there is **no** distinction between a pointer and
an array. A pointer not only directs to some memory address, it is also
the base point, i.e., the index 0, of an array.

```c++
int  n[5] = { 2, 3, 5, 7, 11 };
int* p    = n;   // implicit conversion of array to pointer type!

std::cout << p[0] << std::endl;  // yields n[0]
std::cout << p[1] << std::endl;  // yields n[1]
std::cout << p[4] << std::endl;  // yields n[4]
```

The index operator `[i]` of a pointer `p` gives access to the `i`'th element of the array
starting at address `p`.

---

# Arrays and Dynamic Memory
## Dynamic Memory
Since pointers and arrays are equivalent, one needs to initialize a pointer with the address of
a memory block large enough to hold the wanted array. This is accomplished by **dynamic memory
management**. Note: Memory of arbitrary size can be allocated and deallocated at runtime.

In C++ this is done with the operators `new` and `new[<size>]` to allocate memory and
`delete` and `delete[]` to deallocate memory.

- For a single element:
```c++
<type>* ptr = new <type>;
delete ptr;
```

- For more than one element:
```c++
<type>* array_ptr = new <type>[<size>];
delete[] array_ptr;
```

---

# Arrays and Dynamic Memory
## Dynamic Memory
### Examples:

```c++
char*   s = new char[ 100 ];
int     n = 1024;
double* v = new double[ n ];
float*  f = new float;

for (int i = 0; i < n; ++i)
  v[i] = square(i);   // Note: implicit conversion of i from int to double

*f = 1.41421356237;   // dereference f

// ...

delete[] v;  // new[] => delete[]
delete[] s;
delete   f;  // new   => delete
```

> .h3[Remark:] The size parameter to `new` does not need to be a constant.

---

# Arrays and Dynamic Memory
## Problems with Pointers
The corresponding array to a pointer has no information about the array size.
Remember, that C++ performs no boundary checks. That opens the door to many errors.

```c++
double* v = new double[ 1000 ];
static_assert(std::is_same_v<decltype(v), double*>);  // v is of type double*

// ...

v[2000] = 1.0;
```

With the last instruction, you overwrite a memory position corresponding
to completely other data. The program will typically only terminate, if the memory
does not belong to the program (*segmentation fault*).

---

# Arrays and Dynamic Memory
## Problems with Pointers
The programmer does not know if the memory was allocated or deallocated, except if the pointer
contains `nullptr`:

```c++
double* v = new double[ 1000 ];

// ...

delete[]  v;

// ...

v[100] = 2.0;      // Bug: memory for v is deallocated
```

Again, the last instruction will be executed and will only result in an
immediate error, if the memory is no longer part of the program.

> .h3[Coding Principle:] After calling `delete`, reset the pointer
> value to `nullptr`.

---

# Arrays and Dynamic Memory
## Problems with Pointers
The programmer does not know if the memory was allocated or deallocated, except if the pointer
contains `nullptr`:

```c++
double* v = new double[ 1000 ];

// ...
// Better:
delete[]  v;
v = nullptr;

// ...
if (v != nullptr)
  v[100] = 2.0;      // OK, will not be called
```

> .h3[Coding Principle:] After calling `delete`, reset the pointer
> value to `nullptr`.

---

# Arrays and Dynamic Memory
## Problems with Pointers
Memory addressed by forgotten pointers is lost for the program. C++ does not automatically
delete memory with no references to it (garbage collection).

```c++
void f ()
{
  double* v = new double[ 1000 ];
  ...  // no delete[] v
}
// v is no longer accessible, memory is lost
```

This bug is not directly a problem, since no other data is overwritten.
But if a lot of memory is not deleted after use, the program will have
no available memory left.

> .h3[Coding Principle:] Always make sure, that allocated memory is deallocated after using.

--

> .h3[Remark:] Use tools like *valgrind* to detect such memory errors.

---

# Arrays and Dynamic Memory
## Problems with Pointers

The aftermath of a pointer related bug, e.g. array boundary violation
or accessing deleted memory, may show up *much later* than the
actual position of the error.

### Summary
pointers are "*dangerous*" and require **careful programming**

### Alternatives
There are high-level alternatives in the c++ standard library
- `std::array`  (alternative to static array)
- `std::vector` (alternative to dynamic array)
- `std::span` (make raw arrays a bit safer)
- `std::shared_ptr` and `std::unique_ptr` (alternative to raw pointers)

---

# Arrays and Dynamic Memory
## `std::array<T,size>`

The problems with *static* arrays are:
- no size information
- decays to pointer when passed as argument
- no direct copy operation

```c++
#include <array>

// ...
std::array<int, 3> vec1 = {1, 2, 3};  // explicit type and size
std::array vec2{1.0, 2.0, 3.0};       // deduce type and size from initializer list [c++17]
auto vec3 = vec2;                     // create copy of array
static_assert(vec3.size() == 3);      // access number of elements (static information)

// ...
void f1 (std::array<int,3> arg);      // pass-by-value (copy)
void f2 (std::array<int,3>& arg);     // pass-by-reference
```

---

# Arrays and Dynamic Memory
## `std::vector<T>`

The problems with *dynamic* arrays are:
- no size information
- no copy operation
- must be deleted manually

```c++
#include <cassert>  // for assert(...)
#include <vector>
// ...
int n = 100;
std::vector<double> vec1(n, 0.0);     // construct with size n and default value 0.0
std::vector vec2{1.0, 2.0, 3.0};      // deduce type and size from initializer list [c++17]
auto vec3 = vec2;                     // create copy of array
assert(vec3.size() == 3);             // access number of elements (dynamic information)

// ...
void f1 (std::vector<int> arg);      // pass-by-value (copy)
void f2 (std::vector<int>& arg);     // pass-by-reference
```

---

# Arrays and Dynamic Memory
## `std::span<T,Extend>`

- Arrays do not carry any size information
- `std::span` describes an object that can refer to a contiguous sequence of objects with the first
  element of the sequence at position zero.
- Either *dynamic extend* (dynamic size information) or *static extend*

```c++
#include <cassert>  // for assert(...)
#include <span>
// ...

int a[] { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int b[] { 8, 7, 6 };
int* b_ptr = b;

auto a_span = std::span{a};
auto b_span = std::span{b_ptr, 3};   // or: std::span<int,3>{b_ptr}

assert(a_span.size() == 9);
assert(b_span.size() == 3);
```

---

# Arrays and Dynamic Memory
## `std::shared_ptr<T>` and `std::unique_ptr<T>`

The problems with dynamic allocated memory: ownership is unclear. Who is responsible for releasing the memory?

(1) Shared ownership. Memory is released when the last share is deleted:

```c++
#include <cassert>
#include <memory>

{ // block 1
  std::shared_ptr<int> ptr1 = std::make_shared<int>(5); // allocate memory for int, value 5
  *ptr1 = 6;    // assign new value to memory

  { // block 1.1
    std::shared_ptr<int> ptr2 = ptr1;     // share memory. ptr2 points to same address
    assert(*ptr2 == 6);

  }                                       // end of block 1.1: ptr2 is deleted
}                                         // end of block 1: ptr1 is deleted: memory
                                          // is released
```

---

# Arrays and Dynamic Memory
## `std::shared_ptr<T>` and `std::unique_ptr<T>`

The problems with dynamic allocated memory: ownership is unclear. Who is responsible for releasing the memory?

(2) Unique ownership. Pointer cannot be copied.

```c++
#include <cassert>
#include <memory>

{ // block 1
  std::unique_ptr<int> ptr1 = std::make_unique<int>(5); // allocate memory for int, value 5
  *ptr = 6;     // assign new value to memory

  { // block 1.1
    std::unique_ptr<int> ptr2 = ptr1;     // ERROR: cannot copy unique_ptr

  }
}                                         // end of block 1: ptr1 is deleted: memory
                                          // is released
```
