int main()
{
  { // variant 1
    int log10 = 0;
    for (double num = 12345.0;
         num >= 10.0;
         num /= 10.0, ++log10) ;  // empty loop body
  }

  { // variant 2
    double num = 12345.0;
    for (int log10 = 0; num >= 10.0; ++log10)
      num /= 10.0;
  }
}