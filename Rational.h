#include <cmath>

typedef long Whole; /// Change this to what ever you want
#define FLOAT_READING_PRECISION 10000 /// This is how much detail is considered when reading floats

#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{
    public:
        Rational();
        Rational(Whole topNum);
        Rational(Whole topNum, Whole bottomNum);
        Rational(const double num);

        /** MAKE SURE THESE ARE THE ONLY VARS **/
        Whole N = 0;
        Whole D = 1;
        /** GOT TO KEEP IT LOW LEVEL YOU KNOW **/

        Rational operator+(const Rational &num);
        Rational operator-(const Rational &num);
        Rational operator*(const Rational &num);
        Rational operator/(const Rational &num);
        Rational operator%(const Rational &num);

        void operator+=(const Rational &num);
        void operator-=(const Rational &num);
        void operator*=(const Rational &num);
        void operator/=(const Rational &num);
        void operator%=(const Rational &num);

        bool operator==(const Rational &b);
        bool operator> (const Rational &b);
        bool operator< (const Rational &b);
        bool operator>=(const Rational &b);
        bool operator<=(const Rational &b);

        void operator=(Whole num);
        void operator=(const double num);

        double returnFloat();

    private:
        void setFloat(const double num);
        Whole GCD(const Whole a, const Whole b);
        void simplify();
};

#endif // RATIONAL_H
