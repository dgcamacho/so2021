void foo1(double x)
{
  x += 1.0; // OK: x ist an independent local variable and not const
}

void foo2(double const x)
{
  // x += 1.0; // ERROR: x is a local const variable, can not be changed
}

void foo3(double& x)
{
  x += 1.0; // OK: x is a (mutable) reference to some variable in the calling site
}

void foo4(double const& x)
{
  // x += 1.0; // ERROR: x is a const reference and can thus not be changed
}

int main()
{
  double a = 1.0;
  foo1(a); // a is not changed by that call
  foo2(a); // a is not changed by that call
  foo3(a); // !! a is changed by a call to foo3
  foo4(a); // a is not changed by that call

  // Note: only foo3 requires an actual variable. All other function can be called with simple values
  foo1(1.0);
  foo2(1.0);
  // foo3(1.0); // expected a reference, got a temporary value
  foo4(1.0); // A const reference can bind to pure values, a temporary variable is created that is used inside of the function
}