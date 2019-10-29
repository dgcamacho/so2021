# Floating point numbers

## 1. Difference between float and double
- The terms single and double precision do not actually refer to the precision, but to the number of Bytes used to store
  the value in memory.
- `float` is a single precision floating point type and `double` the double precision floating point type in C++
- Those types correspond to the IEEE 754-2008 standard names `binary32` and `binary64`, respectively.

### Float
- The single precision format uses an 8 bit exponent and 23 bit fraction part
- The minimal subnormal number (exponent = 0 => biased exponent = -127): `+- 1.401,298,4 * 10^-45`
- The minimal normal number (exponent != 0): `+- 1.175,494,3 * 10^-38`
- The maximal number: `+- 3.402,823,4 * 10^38`
- Integers in `[-2^24, 2^24]` can be exactly represented
- Integers in `[-2^25, -2^24-1]` or in `[2^24+1, 2^25]` round to a multiple of 2
- Integers in `[-2^26, -2^25-1]` or in `[2^25+1, 2^26]` round to a multiple of 4

### Double
- The double precision format uses 11 bit exponent and 52 bit fraction part
- The minimal subnormal number (exponent = 0 => biased exponent = -1023): `+- 4.940,656,458,412 * 10^-324`
- The minimal normal number (exponent != 0): `+- 2.225,073,858,507,201,4 * 10^-308`
- The maximal number: `+- 1.797,693,134,862,315,7 * 10^308`
- Integers in `[-2^53, 2^53]` can be exactly represented
- Integers in `[-2^54, -2^53-1]` or in `[2^53+1, 2^54]` round to a multiple of 2
- Integers in `[-2^55, -2^54-1]` or in `[2^54+1, 2^55]` round to a multiple of 4

## 2. Decrementing floating point numbers
- The operator `--x` means: subtract 1 from x
- The value `1.0e8 = 10^8 = 2^26.575`, thus integers can be represented exactly in `double` precision,
  but not in `float` precision.
- The decrement by 1 will thus be rounded to the value before and no progress is made in the loop -> infinite loop for `float`.

## 3. Comparing floating-point expressions
- The number `0.15`, `0.15`, `0.1` and `0.2` might not be representable exactly in both floating-point formats
- The exact result `0.3` is also not representable exactly in floating-point numbers.
- All operations and initializations round to the nearest floating-point number.
- In `float` this by chance results after rounding in the same float number for both expression, in `double` it does not.
- General rule: Do not compare floating-point numbers resulting from mathematical expression by ==.
- Only exactly representable floating point constants, like powers of 2, should be compared. E.g. comparison with 0.0 is
  fine, if you allow that `0 != 1.e-308`.
- Better: Use comparison with a tolerance depending on the machine epsilon (the smallest representable number eps such that `1+eps != 1`)

```c++
assert( std::abs(a - b) < std::numeric_limits<double>::eps );
assert( a >= b - std::numeric_limits<double>::eps );
```
where `std::numeric_limits<double>::eps` is a constant representing the machine epsilon for type `double`.