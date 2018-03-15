#include "Rational.h"

Rational::Rational(){ }

Rational::Rational(Whole topNum)
{ N = topNum; D = 1; }

Rational::Rational(Whole topNum, Whole bottomNum)
{ N = topNum; D = bottomNum; }

Rational::Rational(const double num)
{ setFloat(num); }

/******/

Whole Rational::GCD(const Whole a, const Whole b)
{ return b ? GCD(b, a%b) : a; }

void Rational::simplify()
{
    if(D < 0){ D = -D; N = -N; } /// Numerator is what holds the sign
    const Whole factor = GCD((N < 0) ? -N : N, D);
    N /= factor; D /= factor;
}

/******/

Rational Rational::operator+(const Rational &num)
{
    Rational out(N*num.D + num.N*D, D*num.D);
    out.simplify(); return out;
}

Rational Rational::operator-(const Rational &num)
{
    Rational out(N*num.D - num.N*D, D*num.D);
    out.simplify(); return out;
}

Rational Rational::operator%(const Rational &num)
{
    Rational out(N*num.D % num.N*D, D*num.D);
    out.simplify(); return out;
}

Rational Rational::operator*(const Rational &num)
{
    Rational out(N*num.N, D*num.D);
    out.simplify(); return out;
}

Rational Rational::operator/(const Rational &num)
{
    Rational out(N*num.D, D*num.N);
    out.simplify(); return out;
}

/******/

void Rational::operator+=(const Rational &num)
{
    N *= num.D;
    N += num.N*D;
    D *= num.D;

    simplify();
}

void Rational::operator-=(const Rational &num)
{
    N *= num.D;
    N -= num.N*D;
    D *= num.D;

    simplify();
}

void Rational::operator%=(const Rational &num)
{
    N *= num.D;
    N %= num.N*D;
    D *= num.D;

    simplify();
}

void Rational::operator*=(const Rational &num)
{
    N *= num.N;
    D *= num.D;

    simplify();
}

void Rational::operator/=(const Rational &num)
{
    N *= num.D;
    D *= num.N;

    simplify();
}

/******/

bool Rational::operator==(const Rational &b)
{ return (N*b.D == b.N*D); }

bool Rational::operator>(const Rational &b)
{ return (N*b.D > b.N*D); }

bool Rational::operator<(const Rational &b)
{ return (N*b.D < b.N*D); }

bool Rational::operator>=(const Rational &b)
{ return (N*b.D >= b.N*D); }

bool Rational::operator<=(const Rational &b)
{ return (N*b.D <= b.N*D); }

/******/

void Rational::operator=(Whole num)
{ N = num; D = 1; }

void Rational::operator=(const double num)
{ setFloat(num); }

/******/

double Rational::returnFloat()
{ return ((double)N)/((double)D); }

void Rational::setFloat(const double num)
{
    N = (Whole)(num * FLOAT_READING_PRECISION);
    D = FLOAT_READING_PRECISION;

    simplify();
}

