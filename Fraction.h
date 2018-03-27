/* MIT License
 *
 * Copyright (c) 2018 Samuel R. Belliveau
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
    TEMPLATE SUPPORT:
    char    (Not Recomended)    Because of overflow caused when using a double
    short   (Not Recomended)    Because of overflow caused when using a double to a lesser extent
    long        (Recomended)        This is the perfect size being 32 bits, you get a 64 bit data type
    long long   (Recomended)    This is 64bit so the risk of an overflow is very small, but you do have a 128 bit data type

    ANY FLOAT IS NOT SUPPORTED BECAUSE THEY DO NOT HAVE THE MODULAR FUNCTION, THAT IS THE ONLY REASON.
 */

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
        constexpr Fract(TYPE topNum, TYPE bottomNum) : N{topNum}, D{bottomNum} {}

        constexpr Fract(const long double num)    { setFloat(num); }
        constexpr Fract(const double num)         { setFloat(num); }
        constexpr Fract(const float num)          { setFloat(num); }

        constexpr Fract(const long long int num): N{(TYPE)num}, D{1} {}
        constexpr Fract(const long int num)     : N{(TYPE)num}, D{1} {}
        constexpr Fract(const int num)          : N{(TYPE)num}, D{1} {}
        constexpr Fract(const short int num)    : N{(TYPE)num}, D{1} {}

        /** Casts **/
        explicit constexpr operator short int()      const { return N/D; }
        explicit constexpr operator int()            const { return N/D; }
        explicit constexpr operator long int()       const { return N/D; }
        explicit constexpr operator long long int()  const { return N/D; }

        explicit constexpr operator long double()    const { return ((long double)N)/((long double)D); }
        explicit constexpr operator double()         const { return ((double)N)/((double)D); }
        explicit constexpr operator float()          const { return ((float)N)/((float)D); }

        constexpr void operator=(const long double num)   { setFloat(num); }
        constexpr void operator=(const double num)        { setFloat(num); }
        constexpr void operator=(const float num)         { setFloat(num); }

        constexpr void operator=(const short int num)     { N = (TYPE)num; D = 1; }
        constexpr void operator=(const int num)           { N = (TYPE)num; D = 1; }
        constexpr void operator=(const long long int num) { N = (TYPE)num; D = 1; }
        constexpr void operator=(const long int num)      { N = (TYPE)num; D = 1; }

        /** Operators **/
        // Increment
        constexpr Fract& operator++()
        {
            N = N + D;
            return *this;
        }

        constexpr Fract operator++(int)
        {
            Fract<TYPE> temp(*this);
            operator++();
            return temp;
        }

        // Decrement
        constexpr Fract& operator--()
        {
            N = N - D;
            return *this;
        }

        constexpr Fract operator--(int)
        {
            Fract<TYPE> temp(*this);
            operator--();
            return temp;
        }

        // Add
        constexpr Fract& operator+=(const Fract<TYPE> &b)
        {
            N = N*b.D + D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator+(Fract<TYPE> a, const Fract<TYPE> &b)
        {
            a += b;
            return a;
        }

        // Subtract
        constexpr Fract& operator-=(const Fract<TYPE> &b)
        {
            N = N*b.D - D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator-(Fract<TYPE> a, const Fract<TYPE> &b)
        {
            a -= b;
            return a;
        }

        // Modulo
        constexpr Fract& operator%=(const Fract<TYPE> &b)
        {
            N = N*b.D % D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator%(Fract<TYPE> a, const Fract<TYPE> &b)
        {
            a %= b;
            return a;
        }

        // Multpily
        constexpr Fract& operator*=(const Fract<TYPE> &b)
        {
            N = N * b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator*(Fract<TYPE> a, const Fract<TYPE> &b)
        {
            a *= b;
            return a;
        }

        // Divide
        constexpr Fract& operator/=(const Fract<TYPE> &b)
        {
            N = N * b.D;
            D = D * b.N;
            simplify();
            return *this;
        }

        constexpr friend Fract operator/(Fract<TYPE> a, const Fract<TYPE> &b)
        {
            a /= b;
            return a;
        }

        // Less Than
        constexpr friend bool operator< (const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return (a.N*b.D < a.D*b.N);
        }

        // Greater Than Or Equal To
        constexpr friend bool operator>=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return !(a < b);
        }

        // Greater Than
        constexpr friend bool operator> (const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return (b < a);
        }

        // Less Than Or Equal To
        constexpr friend bool operator<=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return !(a > b);
        }

        // Equals
        constexpr friend bool operator==(const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return (a.N*b.D == a.D*b.N);
        }

        // Not Equals
        constexpr friend bool operator!=(const Fract<TYPE> &a, const Fract<TYPE> &b)
        {
            return !(a == b);
        }

    private:
        /** Background work **/
        // Greatest Common Factor
        inline TYPE GCD(const TYPE a, const TYPE b)
        { return b == 0 ? GCD(b, a%b) : a; }

        // Simplify Fraction
        void simplify()
        {
            if(D < 0){ D = -D; N = -N; } /// Numerator is what holds the sign

            TYPE factor = GCD((N < 0) ? -N : N, D);
            N = N / factor; D = D / factor;
        }
    
        // Take Float And Inturpret It
        void setFloat(FPC num)
        {
            N = (TYPE)(num * 720720 + 0.5); /// 0.5 makes the cast round
            D = 720720;
            simplify();
        }
};

#endif
