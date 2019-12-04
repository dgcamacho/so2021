# Exercise sheet 7 - 2019/12/04

## Exercise 1 (Pointers)
Let `i` have the type `int`, and `p` the type `int *`.
Which of the following expressions are correct,
which are incorrect? Also list the types of the correct ones. Answer without taking concrete values
for `i` and `p` into account.

```c++
i + 1       &p
*p          p + 1
*p + 3      &p == i
&i == p     **(&p)
i == *p     *p + i > i
```


## Exercise 2 (Constness)
Here is a list of function prototypes, some variables and some assignments. Which expressions
aren’t allowed and why?
```c++
int foo ( const int& );
int bar ( int& );

int main()
{
  int i = 0;
  int& j = i;
  static const int f = i;
  int* const p = 0;
  p = &i;
  *p = f;
  const int& l = j;
  const int& k = f;
  foo ( j );
  bar ( l );
  foo ( k );
}
```


## Exercise 3 (Polynomials) :pencil2:
This exercise is about a user-defined type representing polynomials
```math
  P(x) = a_0 + a_1 x + a_2 x^2 + \ldots + a_n x^n\quad (n \geq 0)
```

Write a class for polynomials that should at least contain:
- A constructor receiving the degree of the polynomial;
- A dynamic vector of `coeff_type` (see below) to store the coefficients as member variable;
- A constructor receiving a vector of coefficients $`(a_0,a_1,\ldots)`$;
- An `operator[]` for the access to the individual coefficients;
- A member function (or a free function) returning the degree of the polynomial;
- Arithmetic operations plus and minus (`operator+` and `operator-`);
- (optional) arithmetic operations multiplies and divides (`operator*` and `operator/`);
- An output function for `std::ostream`, i.e. `operator<<`;
- An evaluation function, that makes the polynomial to a *polynomial function*.

The coefficient type of the coefficients $`a_i`$ should be a *typedef* in the class, i.e. `using coeff_type = CONCRETE_TYPE;`.
Use that type to create the vector. (Mathematically, the coefficients must be from a *ring* $`\mathbf{R}`$, e.g. a *field* or
a *quotient ring*).

The argument type to the polynomial $`x`$ must be an $`\mathbf{R}`$*-Algebra*, i.e. something that can be multiplied with
the coefficients. Fix this type in the class as well, i.e. `using value_type = CONCRETE_TYPE;`.

For simplicity here, we use `double` for both. Later we will learn, how to make both flexible, by using placeholders /
templates.

Test your polynomial arithmetic on some reference polynomials:
- The null-polynomial
- The constant function
- Polynomials with just one coefficient unequal to zero
- All coefficients = 1

**>> Submit solution until 2019/12/18 ... (10 Points)**

### Hint:
- Implement an overload for the function `operator<<` for your type:
```c++
std::ostream& operator<<(std::ostream& out, POLYNOMIAL_TYPE const& in);
```
- The evaluation function should be an `operator()`, getting a `value_type` and returning a `value_type`. Use `std::pow` for the
  power of the arguments, or better: write a recursive or iterative implementation yourself, just relying on multiplication.
- The coefficient access function should be implement with const and non-const reference as return type.

### Resources:
- [Wikipedia:Polynomial](https://en.wikipedia.org/wiki/Polynomial), [Wikipedia.de:Polynom](https://de.wikipedia.org/wiki/Polynom),
  [Wikipedia:Polynomial arithmetic](https://en.wikipedia.org/wiki/Polynomial_arithmetic),
  [Wikipedia:Polynomial long division](https://en.wikipedia.org/wiki/Polynomial_long_division)


## Exercise 4 (GotW-4: Class Mechanics)
See [GotW #4](https://herbsutter.com/2013/05/20/gotw-4-class-mechanics).

1. What makes interfaces "easy to use correctly, hard to use incorrectly"? Explain.
2. You are doing a code review. A programmer has written the following class, which shows some poor style and has some real errors. How many can you find, and how would you fix them?
```c++
class complex {
public:
    complex( double r, double i = 0 )
        : real(r), imag(i)
    { }

    void operator+ ( complex other ) {
        real = real + other.real;
        imag = imag + other.imag;
    }

    void operator<<( ostream os ) {
        os << "(" << real << "," << imag << ")";
    }

    complex operator++() {
        ++real;
        return *this;
    }

    complex operator++( int ) {
        auto temp = *this;
        ++real;
        return temp;
    }

    // ... more functions that complement the above ...

private:
    double real, imag;
};
```

Note: This is not intended to be a complete class. For example, if you provide `operator++` you would normally also provide `operator--`. Rather,
this is an instructive example to focus on the mechanics of writing correctly the kinds of functions this class is trying to support.


## Exercise 5: (GotW-88: Const or not const?)
See [GotW #88](https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const).

Is the following code legal C++?
```c++
std::string f() { return "abc"; }

void g() {
  const std::string& s = f();
  std::cout << s << endl;    // can we still use the "temporary" object?
}
```