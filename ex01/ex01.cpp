#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>
#include <cmath>

using namespace std;

rational::rational (int n, int d)
{
  int GCD = gcd(n,d);
  nom = n/GCD;
  den = d/GCD;
  if (den < 0)
  {
    den *= -1;
    nom *= -1;
  }
}

void rational::print()
{
  cout << nom << '/' << den;
}

int rational::gcd (int a, int b)
{
  a = abs(a);
  b = abs(b);
  while (b != 0 and a != 0)
    if (a > b) a %= b;
    else b %= a;
  return a + b;
}

rational rational::add (rational r)
{
  int n = nom * r.den + r.nom * den;
  int d = den * r.den;
  rational sum(n, d);
  return sum;
}

rational rational::sub (rational r)
{
  int n = nom * r.den - r.nom * den;
  int d = den * r.den;
  rational sb(n,d);
  return sb;
}

rational rational::mul (rational r)
{
  int n = nom * r.nom;
  int d = den * r.den;
  rational mlt(n,d);
  return mlt;
}

rational rational::div (rational r)
{
  int n = nom * r.den;
  int d = den * r.nom;
  rational dv(n,d);
  return dv;
}
