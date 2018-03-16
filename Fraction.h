typedef long long Whole; /// Change this to what ever you want
const Whole FLOAT_READING_PRECISION = 10000;

#ifndef FRACTION_H
#define FRACTION_H

class _Fract
{
    public:
        /***** THESE ARE THE ONLY VARS IN THE CLASS *****/
        Whole N = 0;
        Whole D = 1;

        /** Constructors **/
        _Fract();
        _Fract(Whole topNum, Whole bottomNum);
        _Fract(const double num);

        /** Casts **/
        operator Whole();
        operator double();
        void operator=(const double num){ setFloat(num); }

        /** Operators **/
        _Fract operator+(const _Fract &num);
        _Fract operator-(const _Fract &num);
        _Fract operator*(const _Fract &num);
        _Fract operator/(const _Fract &num);
        _Fract operator%(const _Fract &num);
        void operator+= (const _Fract &num);
        void operator-= (const _Fract &num);
        void operator*= (const _Fract &num);
        void operator/= (const _Fract &num);
        void operator%= (const _Fract &num);
        bool operator== (const _Fract &b);
        bool operator>  (const _Fract &b);
        bool operator<  (const _Fract &b);
        bool operator>= (const _Fract &b);
        bool operator<= (const _Fract &b);

    private:
        /** Background work **/
        Whole GCD(const Whole a, const Whole b);
        void setFloat(const double num);
        void simplify();
};

#endif // FRACTION_H
