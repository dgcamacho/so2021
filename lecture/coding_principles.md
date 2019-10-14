# Coding principles and guidelines
Source: "C++ for Scientific Computing", Ronald Kriemann (MPI MIS Leipzig) 2008

## 1. Choice of floating point type
Always check if the range and the precision of the
floating point type is enough for your application. If in
doubt: use double precision.

## 2. variable names
Give your variables a reasonable name.

## 3. RAII
Resource allocation is initialization (RAII):
Whenever a resource, e.g. variable, is allocated/declared,
it should be initialized with some reasonable value.

## 4. const usage
Use const as much as possible.

## 5. pointer init to NULL
Always initialize a pointer with the address of an existing
variable or with NULL.

## 6. float equality test
For floating point types, avoid equality/inequality checks
due to inexact arithmetic.

## 7. parentheses
When in doubt or to clarify the expression: use
parentheses.

## 8. implicit casts
Avoid implicit type conversion.

## 9. default case in switch
Always implement the default case to avoid unhandled
cases.

## 10. const function arguments
Make all function arguments const, except when
changing value (see later).

## 11. return in function
Make sure, that a function has a call to return in every
execution path.

## 12. function naming
Functions implementing the same algorithm on different
types should be named equal.

## 13. functions and minimal evaluation
Never rely on a function call in a logical expression.

## 14. array boundaries
Always make sure, that you access arrays within the valid
index range.

## 15. pointer reset to NULL
After calling delete, reset the pointer value to NULL.

## 16. deallocate pointer
Always make sure, that allocated memory is deallocated
after using.

## 17. string termination
Always ensure, that strings are terminated by `'\0'`.

## 18. type naming
Follow a strict convention in naming new types, e.g. with
special prefix or suffix.

## 19. header encapsulation
Always encapsulate your header files by an
ifndef-define-endif construct.

## 20. global variables
Only if absolutely necessary make non-const variables
global.

## 21. anonymous namespaces
Put module local functions into an anonymous
namespace.

## 22. default copy constructor
Always make sure, that the C++ generated default and
copy constructors behave as expected. If in doubt:
implement constructors by yourself.

## 23. data access in a record
Make all member variables of a record private and allow
read-/write-access only via member functions.

## 24. operator overloading
Only overload operators if necessary and reasonable.

## 25. default copy operator
Always make sure, that the C++ generated copy operator
behaves as expected. If in doubt: implement operator by
yourself.

## 26. detecting errors
- Always check function arguments, especially pointers
  for illegal values (pre condition of a function).
- If a critical situation is possible by an instruction,
  check the operands of the instruction.
- Check, whether the results of a function are as
  expected (function post condition).

## 27. use exceptions
Use exceptions for all error handling.

## 28. dynamic casts
Use dynamic casts for type casting of derived datatypes
as much as possible.