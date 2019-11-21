# Discussion of solution to exercise 4

## Output for float and double
The following output is produced with g++ and no optimization:

### float
```
comparison for type: f and order: default
exp:    1096.63318
kahan:  1096.63318  |kahan-exp|:  0
simple: 1096.63342  |simple-exp|: 0.000244140625
|kahan-simple|: 0.000244140625

comparison for type: f and order: reverse
exp:    1096.63318
kahan:  1096.63318  |kahan-exp|:  0
simple: 1096.63318  |simple-exp|: 0
|kahan-simple|: 0

comparison for type: f and order: random
exp:    1096.63318
kahan:  1096.63318  |kahan-exp|:  0
simple: 1096.63306  |simple-exp|: 0.000122070312
|kahan-simple|: 0.000122070312
```

### double
```
comparison for type d and order default
exp:    1096.6331584284585
kahan:  1096.6331584284585  |kahan-exp|:  0
simple: 1096.6331584284576  |simple-exp|: 9.0949470177292824e-13
|kahan-simple|: 9.0949470177292824e-13

comparison for type d and order reverse
exp:    1096.6331584284585
kahan:  1096.6331584284585  |kahan-exp|:  0
simple: 1096.6331584284585  |simple-exp|: 0
|kahan-simple|: 0

comparison for type d and order random
exp:    1096.6331584284585
kahan:  1096.6331584284585  |kahan-exp|:  0
simple: 1096.6331584284583  |simple-exp|: 2.2737367544323206e-13
|kahan-simple|: 2.2737367544323206e-13
```

## Interpretation
In all cases the *Kahan*-algorithm produced the correct result up to the representable precision of the floating-point type.
This is remarkable, since the simple summation produces 1. different results depending on the order of the arguments, 2. an error
much larger than the machine epsilon for that type. But the best result for simple summation is obtained when the arguments are sorted
in increasing order. A random order is on average better than a large to small order.

With aggressive optimization `-ffast-math` (that allows rearrangement of terms, but may violate strict IEEE conformance), we may get
different results. With my compiler, the default order with `float` produces the largest error with both algorithms, and all other cases
produce the exact result. Probably, the compiler optimizes the Kahan algorithm in such a way that it is replaces with a simple sum. It may
also be, that with some pattern matching the compiler recognizes the process of summing up values of a vector and uses an even more accurate one,
or by default Kahan. Several optimization strategies are possible.

The `clang` I even get another result in the aggressive optimization case. This is, because optimization might be implemented differently in the
compilers. For safe optimization, the result must be the same, but aggressive optimization does not have these guarantees.

## Summary
Be aware of floating-point arithmetic errors. In case of summing up values, prefer increasing order over decreasing order. If a sum values is requested
and your data is sensitive to floating-point errors, you may consider a Kahan algorithm or a variant of it. This may be, for example, the case
in ODE solvers. There you can not change the order of the updates, but may use a more accurate summation.

See also

  Nick Higham: "How and How Not to Sum Floating Point Numbers", in "Accuracy and Stability of Numerical Algorithms", SIAM, 1995

for a more detailed discussion and the example: Euler method. A PDF of the book or just that chapter can be found in the web.