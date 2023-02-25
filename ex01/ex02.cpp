#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#include <cmath>
#endif

using namespace std;

rational::rational(int n, int d)
{
  nom=n;
  den=d;
}

rational check1(int c, int d)
{
  if (c > 0 and d < 0)
  {
    c=-c;
    d=-d;
  }
  else if (c < 0 and d < 0)
  {
    c=abs(c);
    d=abs(d);
  }
  else if (c==0)
    d=abs(d);
  rational aux(c, d);
  return aux;
}

rational operator+ (const rational &x, const rational &y)
{
  int a,b;
  a=(check1(x.nom,x.den).nom)*(check1(y.nom,y.den).den)+(check1(x.nom,x.den).den)*(check1(y.nom,y.den).nom);
  b=(check1(x.nom,x.den).den)*(check1(y.nom,y.den).den);
  rational aux=check1(a,b);
  return aux;
}


rational operator- (const rational &x, const rational &y)
{
  int a,b;
  a=(check1(x.nom,x.den).nom)*(check1(y.nom,y.den).den)-(check1(x.nom,x.den).den)*(check1(y.nom,y.den).nom);
  b=(check1(x.nom,x.den).den)*(check1(y.nom,y.den).den);
  rational aux=check1(a,b);
  return aux;
}

rational operator* (const rational &x, const rational &y)
{
  int a,b;
  a=(check1(x.nom,x.den).nom)*(check1(y.nom,y.den).nom);
  b=(check1(x.nom,x.den).den)*(check1(y.nom,y.den).den);
  rational aux=check1(a,b);
  return aux;
}

rational operator/ (const rational &x, const rational &y)
{
  int a,b;
  a=(check1(x.nom,x.den).nom)*(check1(y.nom,y.den).den);
  b=(check1(x.nom,x.den).den)*(check1(y.nom,y.den).nom);
  rational aux=check1(a,b);
  return aux;
}

int rational::gcd(int a, int b)
{
  a=abs(a);
  b=abs(b);
  while (a > 0 and b > 0)
  {
    if (a > b)
      a=a%b;
    else
      b=b%a;
  }
  return a+b;
}

ostream &operator << (ostream &out, const rational &x)
{
  out << (check1(x.nom,x.den).nom)/(rational::gcd(x.nom,x.den)) << "/" << (check1(x.nom,x.den).den)/(rational::gcd(x.nom,x.den));
  return out;
}
