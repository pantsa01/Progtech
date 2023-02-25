#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Polynomial
{
  protected:
    class Term
    {
      public:
        int exponent;
        int coefficient;
        Term *next;
        Term (int exp, int coeff, Term *n):exponent(exp), coefficient(coeff), next(n) {}
          friend class Polynomial;
    };

  public:
    Polynomial() {head = nullptr;}
    Polynomial(const Polynomial &p);
    ~Polynomial();
    Polynomial & operator = (const Polynomial &p);

    void addTerm(int expon, int coeff);
    double evaluate(double x);

    Polynomial operator += (const Polynomial &p);
    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q);
    friend Polynomial operator* (const Polynomial &p, const Polynomial &q);
    friend ostream & operator << (ostream &out, const Polynomial &p);

  private:
    Term *head;
    string monomialPrint (int exp, int coeff, bool first) const;
    Polynomial multiplyRow (Term *t) const;
};

Polynomial::Polynomial(const Polynomial &p)
{
  if (p.head == nullptr) {head = nullptr; return;}
  else head = new Term (p.head->exponent, p.head->coefficient, nullptr);

  Term* temp = head;
  Term* ptemp = p.head->next;
  while (ptemp != nullptr)
  {
    temp->next = new Term (ptemp->exponent, ptemp->coefficient, nullptr);
    ptemp = ptemp->next;
    temp = temp->next;
  }
}

Polynomial::~Polynomial()
{
  if(head == nullptr) return;
  Term* cur = head, *nxt;
  while (cur != nullptr)
  {
    nxt = cur->next;
    delete cur;
    cur = nxt;
  }
}


Polynomial& Polynomial::operator = (const Polynomial &p)
{
  Polynomial temp(p);
  swap (head, temp.head);
  return *this;
}


void Polynomial::addTerm(int expon, int coeff)
{
  if (head == nullptr)
  {
    Term *newterm = new Term (expon, coeff, nullptr);
    head = newterm;
    return;
  }
  else if (expon > head->exponent)
  {
    Term *newterm = new Term(expon, coeff, head);
    head = newterm;
    return;
  }
  else if(expon == head->exponent)
  {
    if (coeff + head->coefficient != 0)
      head->coefficient += coeff;
    else
    {
      Term* temp = head;
      head = head->next;
      delete temp;
    }
    return;
  }

  Term *prev = head, *cur = head->next;
  while (cur != nullptr and cur->exponent > expon)
  {
    prev = cur;
    cur = prev->next;
  }
  if (cur == nullptr or expon != cur->exponent)
  {
    Term* newterm = new Term (expon, coeff, prev->next);
    prev->next = newterm;
  }
  else if (coeff + cur->coefficient != 0)
    cur->coefficient += coeff;
  else
  {
    prev->next = cur->next;
    delete cur;
  }
}


double Polynomial::evaluate(double x)
{
  double sum = 0;
  for (Term *temp = head; temp != nullptr; temp = temp->next)
  {
    if (temp->exponent != 0)
      sum += (temp->coefficient * pow(x, temp->exponent));
    else sum += temp->coefficient;
  }
  return sum;
}


string Polynomial::monomialPrint(int exp, int coeff, bool first) const
{
  string result;
  if(!first) result += ' ';
  if (coeff < 0){result += "- "; coeff *= -1;}
  else if (!first) result += "+ ";

  if (coeff != 1 or exp == 0)
    result += to_string(coeff);
  if (exp > 1) result += ("x^" + to_string(exp));
  else if (exp == 1) result += "x";
  return result;
}

ostream & operator << (ostream &out, const Polynomial &p)
{
  if (p.head == nullptr)
  {
    out << 0;
    return out;
  }
  out << p.monomialPrint (p.head->exponent, p.head->coefficient, true);
  for (Polynomial::Term *temp = p.head->next; temp != nullptr; temp = temp->next)
    out << p.monomialPrint (temp->exponent, temp->coefficient, false);
  return out;
}


Polynomial operator+ (const Polynomial &p, const Polynomial &q)
{
  Polynomial sum(p);
  for (Polynomial::Term* temp = q.head; temp != nullptr; temp = temp->next)
    sum.addTerm(temp->exponent, temp->coefficient);
  return sum;
}

Polynomial Polynomial::operator += (const Polynomial &p)
{
  for (Term* temp = p.head; temp != nullptr; temp = temp->next)
    this->addTerm(temp->exponent, temp->coefficient);
  return *this;
}


Polynomial Polynomial::multiplyRow (Term *t) const
{
  Polynomial product;
  for (Term* temp = head; temp!=nullptr; temp = temp->next)
    product.addTerm(temp->exponent + t->exponent, temp->coefficient * t->coefficient);
  return product;
}

Polynomial operator* (const Polynomial &p, const Polynomial &q)
{
  Polynomial product;
  if (p.head == nullptr or q.head == nullptr) return product;

  for(Polynomial::Term *temp = q.head;temp != nullptr; temp = temp->next)
    product += p.multiplyRow(temp);
  return product;
}
