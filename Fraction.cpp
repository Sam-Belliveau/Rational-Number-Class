#include "Fraction.h"

/** Constructors **/

_Fract::_Fract(){ }

_Fract::_Fract(const double num)
{ setFloat(num); }

_Fract::_Fract(Whole topNum, Whole bottomNum)
{ N = topNum; D = bottomNum; }

/** Casts **/

_Fract::operator Whole() { return N/D; }
_Fract::operator double(){ return ((double)N)/((double)D); }

/** Operators **/

// Normal

_Fract _Fract::operator+(const _Fract &num)
{
    _Fract out(N*num.D + num.N*D, D*num.D);
    out.simplify(); return out;
}

_Fract _Fract::operator-(const _Fract &num)
{
    _Fract out(N*num.D - num.N*D, D*num.D);
    out.simplify(); return out;
}

_Fract _Fract::operator*(const _Fract &num)
{
    _Fract out(N*num.N, D*num.D);
    out.simplify(); return out;
}

_Fract _Fract::operator/(const _Fract &num)
{
    _Fract out(N*num.D, D*num.N);
    out.simplify(); return out;
}

_Fract _Fract::operator%(const _Fract &num)
{
    _Fract out(N*num.D % num.N*D, D*num.D);
    out.simplify(); return out;
}

// Self Modifying

void _Fract::operator+=(const _Fract &num)
{
    N *= num.D;
    N += num.N*D;
    D *= num.D;

    simplify();
}

void _Fract::operator-=(const _Fract &num)
{
    N *= num.D;
    N -= num.N*D;
    D *= num.D;

    simplify();
}

void _Fract::operator%=(const _Fract &num)
{
    N *= num.D;
    N %= num.N*D;
    D *= num.D;

    simplify();
}

void _Fract::operator*=(const _Fract &num)
{
    N *= num.N;
    D *= num.D;

    simplify();
}

void _Fract::operator/=(const _Fract &num)
{
    N *= num.D;
    D *= num.N;

    simplify();
}

// Comparison

bool _Fract::operator==(const _Fract &b)
{ return (N*b.D == b.N*D); }

bool _Fract::operator>(const _Fract &b)
{ return (N*b.D > b.N*D); }

bool _Fract::operator<(const _Fract &b)
{ return (N*b.D < b.N*D); }

bool _Fract::operator>=(const _Fract &b)
{ return (N*b.D >= b.N*D); }

bool _Fract::operator<=(const _Fract &b)
{ return (N*b.D <= b.N*D); }

/** Background Work **/

Whole _Fract::GCD(const Whole a, const Whole b)
{ return b ? GCD(b, a%b) : a; }

void _Fract::setFloat(const double num)
{
    if((double)(Whole)num == num) { N = (Whole)num; D = 1; return; }

    N = (Whole)(num * FLOAT_READING_PRECISION); /// 0.5 makes the cast round
    D = FLOAT_READING_PRECISION; /// The Precision Multiplier is simplified

    simplify();
}

void _Fract::simplify()
{
    if(D < 0){ D = -D; N = -N; } /// Numerator is what holds the sign
    if(D == 0){ D = 1; }

    const Whole factor = GCD((N < 0) ? -N : N, D);
    N /= factor; D /= factor;
}

