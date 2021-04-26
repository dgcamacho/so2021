int main()
{
  double  f[5];

  for (int i = 0; i < 5; ++i)   // Ok
    f[i] = 2*i;

  for (int i = 0; i <= 5; ++i)  // Bug
    f[i] = 2*i;
}