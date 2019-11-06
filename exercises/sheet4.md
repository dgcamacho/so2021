# Exercise sheet 4 - 2019/11/06

## Exercise 1 (Work with references and constants)
*References* are aliases to existing objects or functions. In contrast to pointers, references are
not just addresses, but refer to the data behind that addresses. They can be used like regular variables
and are declared with the symbol `&`:
```c++
TYPE & VARNAME = OBJECT;
```
So, the reference variable `VARNAME` now binds to the aliased object `OBJECT`. References must be initialized
directly and are always bound to one object.

A data-type with the qualifier `const` is called a *constant* ans is immutable. It can be declared as
```c++
TYPE const VARNAME = VALUE;
```
Constants can not be modified and thus must be initialized directly.

1. Write a function `foo(...)` that gets one argument, either
    - `double` value
    - `double const` value
    - `double` reference,
    - `double const` reference,
   Change the value of the referenced data inside the function. Is it always possible?
2. Define functions `f(char)`, `g(char&)`, and `h(char const&)`. Call them with the arguments `'a'`,
`49`, `3300`, `c`, `uc`, and `sc`, where `c` is a `char`, `uc` is an `unsigned char`, and `sc` is a `signed char` variable.
Which calls are legal? Which calls cause the compiler to introduce a *temporary variable*?


## Exercise 2 (Structs)
A `struct` in C++ is one type of class encapsulating data and methods that act on this data.
The most simple structs are those just containing data. In this sense a `struct` is a compound data-type.
Each data-type has a size in memory. This can be evaluated with `sizeof(TYPE)` or `sizeof(EXPRESSION)`.
The actual total size of the data-type might depend on its members and the order of its members.

1. Define a `struct` with a member of each of the types `bool`, `char`, `int`, `long`, `double`, and `long double`.
Order the members so as to get the largest size of the struct and the smallest size of the struct.
2. What is the size of an empty `struct` without any member variables? Why?

### Note
- While you might get different sizes of the struct type when reordering the members, this saving seems to be small, but
  when you allocate a vector of that many of these types, you might end up with large memory savings.
- But be aware of the fact, that the order of members does not only affect the memory size, but also the
  read and write performance when accessing the members. See the blog post of Jonas Devlieghere from below.

### Resources
- [cppreference:class](https://en.cppreference.com/w/cpp/language/class)
- https://jonasdevlieghere.com/order-your-members/


## Exercise 3 (Code formatting)
It is recommended to follow some code style guidelines. Be consistent with naming, indentation, brackets, etc. This is not
for the compiler. A program can read any valid source code. But it is for you now, for your coworkers or for you in the future when
you reopen some old code. Style your code consistently from the first line.

A minimal guideline is given in the README. But there is more. And there are different common styles. Sometimes you get code from someone
else and need to read/understand it. A good starting point is to transform the code to your code style. This can be automated.

In `material/sheet4/exercise3.cc` you can find a horribly complicated unreadable code. Reformat it, using some tools:
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [astyle](http://astyle.sourceforge.net/)
- [uncrustify](http://uncrustify.sourceforge.net/)

### Resources
- [Google code style](https://google.github.io/styleguide/cppguide.html),
- [Indentation styles](https://en.wikipedia.org/wiki/Indentation_style)
- [Cpp Core guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)



## Exercise 4 (Rational numbers) :pencil2:
Write a class for rational numbers. The number should always be represented as *fully reduced fraction* of the form
```math
\frac{\text{numerator}}{\text{denominator}}
```
with $`\text{denominator} > 0`$.

1. What is an appropriate data structure for rational numbers?
2. Start by writing a function `int gcd(int,int)` (greatest common devisor), you will need it to reduce fractions
    - You can use the Euclidean algorithm to determine the greatest common devisor.
    - For an algorithm, see https://en.wikipedia.org/wiki/Greatest_common_divisor
    - Implement this scheme as a recursive function.
3. Write a class `Rational`, which represents a rational number. The constructor should have the numerator and the
   denominator as arguments. Be sure to check for valid input. In addition, the class has two functions `numerator()` and `denominator()` that return the values of the numerator and denominator, respectively. The class should have three constructors:
    - a default constructor that initializes the fraction with 1,
    - a constructor that initializes the fraction with a given numerator and denominator, and
    - a constructor that initializes the fraction with a given whole number.
4. Supplement the class with operators for `*= += -= /=` and `==`.
5. Use the newly implemented methods to implement free operators `* + - /`.
6. Check your implementation using various test cases. Initialize three fractions
   ```math
   f_1 = -\frac{3}{12},\; f_2=\frac{4}{3},\; f_3=\frac{0}{1}.
   ```
   Test the operators with the following examples
   ```math
   f_1 + f_2,\; f_1\cdot f_2,\; 4 + f_2,\; f_2 + 5,\; 12\cdot f_1,\; f_1\cdot 6,\; \frac{f_1}{f_2}
   ```
   Print the result after each operation. The corresponding solutions are
   ```math
   \frac{13}{12},\; -\frac{1}{3},\; \frac{16}{3},\; \frac{19}{3},\; -\frac{3}{1},\; -\frac{3}{2},\; -\frac{3}{16}.
   ```

**>> Submit solution until 2019/11/27 ... (10 Points)**

### Resources
- [GCD](https://en.wikipedia.org/wiki/Greatest_common_divisor)


## Exercise 5 (Duff's device)
What does the following example do?
```c++
int func(std::vector<int> const& data)
{
  int to = 0;
  int count = data.size();
  int n = (count + 7)/8;
  int i = 0;
  switch (count % 8) {
    case 0: do { to += data[i++];
    case 7: to += data[i++];
    case 6: to += data[i++];
    case 5: to += data[i++];
    case 4: to += data[i++];
    case 3: to += data[i++];
    case 2: to += data[i++];
    case 1: to += data[i++];
    } while (--n > 0);
  }
  return to;
}
```
Why would anyone write something like that? No, this is not recommended as good style!

### Resources
- [Wikipedia:Duffs_Device](https://en.wikipedia.org/wiki/Duff%27s_device)
- [mailinglist post by Tom Duff](https://www.lysator.liu.se/c/duffs-device.html)
- Search for Loop unrolling for more information.