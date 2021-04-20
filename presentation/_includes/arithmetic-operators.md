---
class: center, middle
# Arithmetic Operators and Assignment Operators
---

# Arithmetic and Assignment Operators
## Arithmetic
For integer and floating point types:

```c++
  x + y;
  x - y;
  x * y;
  x / y;
```

For integer types, the **modulus** operator:

```c++
  x % y;
```

> .h3[Remark:] No operator for power, like `^` in Matlab or `**` in Python!

---

# Arithmetic and Assignment Operators
## Assignment
Standard assignment (as with initial values)

```c++
  x = y;
```

Assignment can be combined with arithmetic, so

```c++
  x = x + y;  x = x - y;
  x = x * y;  x = x / y;
  x = x % y;             // for integers
```

is the same as

```c++
  x += y;  x -= y;
  x *= y;  x /= y;
  x %= y;                // for integers
```

These are called **compound assignment** operators.

---

# Arithmetic and Assignment Operators
## Increment and Decrement
In C++ (like in C) exist special versions for
variable increment/decrement:

```c++
int  n = 0;

++n; // same as n = n + 1 or n += 1
n++;
--n; // same as n = n - 1 or n -= 1
n--;
```

Difference between **preincrement** and **postincrement**,
e.g.

```c++
int  n = 5, m = 5 * n++;
```

results in `n = 6` and `m = 25`, whereas

```c++
int  n = 5, m = 5 * ++n;
```

results in `n = 6` and `m = 30`.

---

# Arithmetic and Assignment Operators
## Examples

```c++
int  n1 = 3, n2 = 4;
int  n3 = 0;

n3  = 2 * n1 - n2 + n1 / 2;
n2 *= 6;
n1 -= 8;

double const approx_pi = 355.0 / 113.0;

double f1  = approx_pi / 2.0;
double f2  = approx_pi * approx_pi + 10.0 * f1;
f1 /= 5.0;
```

> .h3[Attention:] The division `355/113` for integers is different than for floats `355.0/113.0`

> .h3[Remark:] If you mix integer and float the operands are (implicitly) converted (cast) to the floating
> point type first.

---

# Arithmetic and Assignment Operators
## Division by Zero and other undefined Operations
### With floating point types:
- For \(x \ne 0.0\): \(x / 0.0 =\) `Inf`, with `Inf` is a special floating point number for infinity.
- For \(x = 0.0\): \(x / 0.0 =\) `NaN` (not-a-number) is another special floating point number for
  *invalid* or *not defined* results, e.g., square root of negative numbers.

Both operations are (usually) performed without notification, i.e., the
program continues execution with these numbers. NaNs often occur with
uninitialized variables, therefore RAII!

> .h3[Remark:] Check with `std::isnan` and `std::isinf` whether a result is NaN or Inf.

---

# Arithmetic and Assignment Operators
## Division by Zero and other undefined Operations
### With floating point types:
- For \(x \ne 0.0\): \(x / 0.0 =\) `Inf`, with `Inf` is a special floating point number for infinity.
- For \(x = 0.0\): \(x / 0.0 =\) `NaN` (not-a-number) is another special floating point number for
  *invalid* or *not defined* results, e.g., square root of negative numbers.

Both operations are (usually) performed without notification, i.e., the
program continues execution with these numbers. NaNs often occur with
uninitialized variables, therefore RAII!

### In integer arithmetic:
\(x / 0\) leads to **undefined behavior**, i.e., the
program (usually) aborts.

---

# Relational and Logical Operators
## Comparison
Standard comparison for integer and floating point types:

```c++
  x >  y;   // bigger than
  x <  y;   // less than
  x >= y;   // bigger or equal
  x <= y;   // less or equal
  x == y;   // equal
  x != y;   // unequal
```

Logic Logical operators `and`, `or` and `not`
for boolean values:

```c++
  b1 && b2;  // and
  b1 || b2;  // or
  ! b1;      // not
```

---

# Relational and Logical Operators
## Sequenced evaluation
Logical expressions are only evaluated until the
result is known. This is important if the expression contains function
calls (see later), or a sub expression is only allowed if a previous sub
expression is `true`.

```c++
int  x = 2;
int  y = 4;
int  z = 4;

// z == 4 is not tested
bool b = (x == 2 && y == 3 && z == 4);

// only x == 2 is tested
b = (x == 2 || y == 3 || z == 4);

// correct, since x != 0 in "y/x"
b = (x != 0 && y / x > 1);
```

---

# Relational and Logical Operators
## Floating Point Comparison

> .h3[Coding Principle:] For floating point types, avoid equality checks due to
> inexact arithmetic.

Better is interval test:

```c++
double f1 = std::sqrt(2.0);
double f2 = f1 * f1;

bool b = (f2 == 2.0);                  // unsafe

double const eps = 1e-14;

b = f2 > 2.0 - eps && f2 < 2.0 + eps;  // safe
b = std::abs(f2 - 2.0) < eps;          // better
```

--

> .h3[Note:] Floating point numbers are not equally distributed

---

# Relational and Logical Operators
## Floating Point Comparison

- Accuracy of numerical algorithms often measured in "ULPs" -
  [units in the last place](https://en.wikipedia.org/wiki/Unit_in_the_last_place)
- Comparison up to "some" ULPs
- `std::numeric_limits` provides *eps*

```c++
double const eps = std::numeric_limits<double>::epsilon();
double const min = std::numeric_limits<double>::min();

int const ulp = 2;
bool b = std::abs(x-y) <= eps * std::abs(x+y) * ulp || std::abs(x-y) < min;
```

> .h3[Remark:] Mathematical functions often have an accuracy of a few ULPs, see
> [Errors-in-Math-Functions](https://www.gnu.org/software/libc/manual/html_node/Errors-in-Math-Functions.html)

---

# Precedence and Associativity of Operators
## Precedence
When evaluating complex expressions, what is evaluated first,
and in which order? Example:

```c++
int   n1 = 2 + 3 * 4 % 2 - 5;
int   n2 = 4;
bool  b  = n1 >= 4 && n2 != 3 || n1 < n2;
```

Precedence of arithmetics follows algebraic/logical precedence, e.g.,
`*` before `+`, `&&` before `||`. Increment (`++`) and decrement (`--`) have higher, assignment
(`=`, `+=`, ...) has lower priority.

*Parentheses* have highest priority.

```c++
int   n1 = (2 + ((3 * 4) % 2) - 5);
int   n2 = 4;
bool  b  = (((n1 >= 4) && (n2 != 3)) || (n1 < n2));
```

---

# Precedence and Associativity of Operators
## Precedence
### Example
The operator `^` does not represent the power operator. It represents a logical XOR and has the wrong precedence
for exponentiation.

```c++
int a = b^2 + c;

// is equivalent to:
int a = b^(2 + c);

// but NOT to (b^2) + c
```

> .h3[Principle:] When in doubt or to clarify an expression: use parentheses.

---

# Precedence and Associativity of Operators
## Associativity
Arithmetic and logical operators are **left associative**,
whereas assignment operators are **right associative**:

```c++
int  n1 = 1 + 2 + 3 + 4;
int  n2 = 1 * 2 * 3 * 4;
int  n3, n4 , n5;

n3 = n4 = n5 = 0;
```

is the same as

```c++
int  n1 = (((1 + 2) + 3) + 4);
int  n2 = (((1 * 2) * 3) * 4);
int  n3, n4 , n5;

(n3 = (n4 = (n5 = 0)));
```

---

# Precedence and Associativity of Operators
## Summary

https://en.cppreference.com/w/cpp/language/operator_precedence

| **Priority** |  **Associativity** |  **Operators** |
|--------------|--------------------|----------------|
|  highest     | left               | `++`, `--` (postfix) |
|              | right              | `++`, `--` (prefix), `-` (unary), `!`, `&` (address), `*` (deref) |
|              | left               | `*` (multiplication), `/`, `%` |
|              | left               | `+`, `-`       |
|              | left               | `>`, `<`, `>=`, `<=` |
|              | left               | `==`, `!=`     |
|              | left               | `&&`           |
|              | left               | \(\vert\vert\) |
|   lowest     | right              | `=`, `+=`, `-=`, `*=`, `/=`, `%=` |
