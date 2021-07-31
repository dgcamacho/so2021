// (a)
double func1a(double x) { return (2*x); } // add an argument, or...
double func1b(double) { return 2; }       // do not rely on any argument. The argument name is optional, if it is not used.

// (b)
double func2(double x) { return 2 * x; }  // Semicolon after return statement

// (c) return statement is missing and maybe the intend of the function is wrong
double func3a(double& x) { return x *= 2; } // Reference-argument, otherwise the assignment has no effect. Add a return statement.
void func3b(double& x) { x *= 2; }          // If no return statement is added, declare the function as void.

// (d) Can not return non-ref variable by reference!
double& func4(double& x) { return x; }   // pass argument as reference. Then it can be returned.

// (e)
double* func5(double& x) { return &x; }  // If an "&" operator is used on the reference, the address is returned. Thus, change the return type to pointer.

// (f) No error.
double& func6(double& x) { return x; } // OK Returning the passed reference by reference is fine.