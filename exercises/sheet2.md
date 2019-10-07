# Exercise sheet 2 - 2019/10/23

Zur Berechnung der Wurzel einer reellen Zahl $a>0$ verwende man ein Newton-Verfahren zur Bestimmung der Nullstelle einer Funktion $f$:

```math
  f(x) := x^2 - a = 0.
```

Ausgehend von der Iterationsvorschrift $`x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}`$ implementiere man eine Funktion
`double sqrt_recursiv(double a, double x0, unsigned int n)` die *rekursiv* die Wurzel von $a$ bestimmt.
Teste dies für eine Rekursionstiefe $`n=5, 10, 100`$ für $`a=10`$ und Startwert $`x_0=3`$.

Was ist der Unterschied zu einer iterativen Umsetzung des Verfahrens?

