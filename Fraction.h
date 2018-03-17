typedef long double FPC; /// floating point calculator

#ifndef FRACTION_H
#define FRACTION_H

template<typename TYPE>
class Fract
{
    public:
        /***** THESE ARE THE ONLY VARS IN THE CLASS *****/
        TYPE N = 0;
        TYPE D = 1;

        /** Constructors **/
        Fract(TYPE topNum, TYPE bottomNum) : N{topNum}, D{bottomNum} {}

        Fract(const long double num) { setFloat(num); }
        Fract(const double num)      { setFloat(num); }
        Fract(const float num)       { setFloat(num); }

        /** Casts **/
        operator char()             const { return N/D; }
        operator short()            const { return N/D; }
        operator int()              const { return N/D; }
        operator long int()         const { return N/D; }
        operator long long int()    const { return N/D; }

        operator long double()  const { return ((long double)N)/((long double)D); }
        operator double()       const { return ((double)N)/((double)D); }
        operator float()        const { return ((float)N)/((float)D); }

        void operator=(const long double num)   { setFloat(num); }
        void operator=(const double num)        { setFloat(num); }
        void operator=(const float num)         { setFloat(num); }

        void operator=(const char num)      { N = (TYPE)num; D = 1; }
        void operator=(const short num)     { N = (TYPE)num; D = 1; }
        void operator=(const int num)       { N = (TYPE)num; D = 1; }
        void operator=(const long int num)  { N = (TYPE)num; D = 1; }
        void operator=(const long long num) { N = (TYPE)num; D = 1; }

        /** Operators **/
        Fract& operator++()
        { N += D; return *this; }

        Fract operator++(int)
        { Fract<TYPE> temp(*this); operator++(); return temp; }

        Fract& operator--()
        { N -= D; return *this; }

        Fract operator--(int)
        { Fract<TYPE> temp(*this); operator--(); return temp; }


        Fract& operator+=(const Fract<TYPE> &b)
        {
            N = N*b.D + D*b.N;
            D *= b.D;
            simplify();
            return *this;
        }

        friend Fract operator+(Fract<TYPE> a, const Fract<TYPE> &b)
        { a += b; return a; }

        Fract& operator-=(const Fract<TYPE> &b)
        {
            N = N*b.D - D*b.N;
            D *= b.D;
            simplify();
            return *this;
        }

        friend Fract operator-(Fract<TYPE> a, const Fract<TYPE> &b)
        { a -= b; return a; }

        Fract& operator%=(const Fract<TYPE> &b)
        {
            N = N*b.D % D*b.N;
            D *= b.D;
            simplify();
            return *this;
        }

        friend Fract operator%(Fract<TYPE> a, const Fract<TYPE> &b)
        { a %= b; return a; }

        Fract& operator*=(const Fract<TYPE> &b)
        {
            N *= b.N;
            D *= b.D;
            simplify();
            return *this;
        }

        friend Fract operator*(Fract<TYPE> a, const Fract<TYPE> &b)
        { a *= b; return a; }

        Fract& operator/=(const Fract<TYPE> &b)
        {
            N *= b.D;
            D *= b.N;
            simplify();
            return *this;
        }

        friend Fract operator/(Fract<TYPE> a, const Fract<TYPE> &b)
        { a /= b; return a; }


        friend bool operator< (const Fract<TYPE> &a, const Fract<TYPE> &b)
        { return (a.N*b.D < a.D*b.N); }
        /**/
        /**/friend bool operator>=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        /**/{ return !(a < b); }
        /**/
        /**/friend bool operator> (const Fract<TYPE> &a, const Fract<TYPE> &b)
        /**/{ return (b < a); }
        /******/
        /******/friend bool operator<=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        /******/{ return !(a > b); }

        friend bool operator==(const Fract<TYPE> &a, const Fract<TYPE> &b)
        { return (a.N*b.D == a.D*b.N); }
        /**/
        /**/friend bool operator!=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        /**/{ return !(a == b); }

    private:
        /** Background work **/
        inline TYPE GCD(const TYPE a, const TYPE b)
        { return b ? GCD(b, a%b) : a; }

        void simplify()
        {
            if(D < 0){ D = -D; N = -N; } /// Numerator is what holds the sign
            if(D == 0){ D = 1; }

            TYPE factor = GCD((N < 0) ? -N : N, D);
            N /= factor; D /= factor;
        }

        /// Small enough to avoid overflows,
        /// enough factors to get good results
        const TYPE TheHolyGrail = 0x13B0; // does not need to be in hex, I just look like a hacker
        void setFloat(FPC num)
        {
            N = (TYPE)(num * TheHolyGrail + 0.5); /// 0.5 makes the cast round
            D = TheHolyGrail;
            simplify();
        }
};

#endif
