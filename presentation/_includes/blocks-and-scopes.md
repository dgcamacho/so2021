---
class: center, middle
# Blocks and Scope
---

# Blocks and Scope
## Blocks
Statements in a C++ program are part of a *block*,
which is enclosed by `{` and `}`:

```c++
{ // ...
}
```

> .h3[Remark:] The trivial block is defined by a single statement.

Blocks can be arbitrarily nested or otherwise put together:

```c++
{ // block 1
    { // subblock 1.1
    }
    { // subblock 1.2
        { // sub subblock 1.2.1
        }
    }
}
```

---

# Blocks and Scope
## Variable Scope
Variables can be declared in each block individually,
even with the same name:

```c++
{ // block 1
    int     n1 = 1;
    double  f1 = 0.0;
}
{ // block 2
    int     n1 = 2;   // n1 has value 2 in this block
}

```

but not twice in the same block:

```c++
{
    int  n1 = 1;
    // ...
    int  n1 = 2;   // ERROR
}

```

---

# Blocks and Scope
## Variable Scope
A variable is declared in the *local* block and
all *enclosed* blocks:

```c++
{ // block 1:             n1 declared
    int  n1 = 1;

    { // block 1.1:       n1, n2 declared
        int  n2 = 2;

        { // block 1.1.1: n1, n2 declared
        }
    }

    int  n4 = 4;

    { // block 1.2:       n1, n4, n3 declared
        int  n3 = 3;
    }
}
```

---

# Blocks and Scope
## Variable Scope
Variables with the same name can also be declared in nested blocks.

```c++
{ // block 1
    int  n1 = 1;       // n1 == 1

    { // block 1.1
        int  n1 = 2;   // n1 == 2
    }
                       // n1 == 1
    { // block 1.2
        int  n1 = 3;   // n1 == 3
    }
    { // block 1.3
        n1 = 4;
    }
                       // n1 == 4 !!!
}
```
\(\rightarrow\) inner variable hides name of the outer variable.
---

# Blocks and Scope
## Variable Scope
A reference to a variable will always be made to the **first** declaration found when going up
the hierarchy of enclosing blocks.

```c++
{ // block 1
    int  m = 0, n1 = 1;

    { // block 1.1
        int  n2 = 2;

        { // block 1.1.1
            m = n1 + n2;   // evaluates to m = 3
        }
    }
    { // block 1.2
        int  n2 = 3;

        m = n1 + n2;       // evaluates to m = 4
    }
}
```

---

# Blocks and Scope
## Variable Scope

> .h3[Remark:] Using variables with same name in nested blocks is not recommended,
> since that often leads to erroneous programs.

---

# Blocks and Scope
## Variable Lifetime
The scope of a variable also defines their *lifetime*, e.g., the time where resources are needed
for the variable. For non-`static` variables, memory is allocated if a declaration is encountered
and released, when the leaving the block holding the declaration:

```c++
{   int  n = 0;          // memory for an integer is allocated
    {
        double f = 1.2;  // memory for a double is allocated
        ...
    }                    // memory for "f" is released
}                        // memory for "n" is released
```

--

For `static` variables, the memory will never be released and only allocated once per program run:

```c++
{
    static int m = 10;   // allocate memory once
}                        // memory for "m" is not released
```
