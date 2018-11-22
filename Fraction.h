
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

#ifndef FRACTION_H
#define FRACTION_H
#include <ostream>

template<typename TYPE, bool SAFE = true>
class Fract
{
    public:
        /***** THESE ARE THE ONLY VARS IN THE CLASS *****/
        TYPE N = 0;
        TYPE D = 1;

        /** Constructors **/
        constexpr Fract(const TYPE topNum, const TYPE bottomNum) : N{topNum}, D{bottomNum} {}
    
        template<typename iTYPE>
        constexpr Fract(const Fract<iTYPE> in) : N{static_cast<TYPE>(in.N)}, D{static_cast<TYPE>(in.D)} {}

        Fract() = default;
    
        template<class NUM_T>
        Fract(const NUM_T num) { setNum(num); }

        template<class NUM_T>
        void operator=(const NUM_T num) { setNum(num); }

        /* Casts */
        template<class NUM_T>
        explicit constexpr operator NUM_T() const { return NUM_T(N)/NUM_T(D); }

        /** Operators **/
        // Increment
        constexpr Fract& operator++()
        {
            N = N + D;
            return *this;
        }

        constexpr Fract operator++(int)
        {
            Fract<TYPE, SAFE> temp(*this);
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
            Fract<TYPE, SAFE> temp(*this);
            operator--();
            return temp;
        }

        // Add
        constexpr Fract& operator+=(const Fract<TYPE, SAFE> &b)
        {
            N = N*b.D + D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator+(Fract<TYPE, SAFE> a, const Fract<TYPE, SAFE> &b)
        {
            a += b;
            return a;
        }

        // Subtract
        constexpr Fract& operator-=(const Fract<TYPE, SAFE> &b)
        {
            N = N*b.D - D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator-(Fract<TYPE, SAFE> a, const Fract<TYPE, SAFE> &b)
        {
            a -= b;
            return a;
        }

        // Modulo
        constexpr Fract& operator%=(const Fract<TYPE, SAFE> &b)
        {
            N = N*b.D % D*b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator%(Fract<TYPE, SAFE> a, const Fract<TYPE, SAFE> &b)
        {
            a %= b;
            return a;
        }

        // Multpily
        constexpr Fract& operator*=(const Fract<TYPE, SAFE> &b)
        {
            N = N * b.N;
            D = D * b.D;
            simplify();
            return *this;
        }

        constexpr friend Fract operator*(Fract<TYPE, SAFE> a, const Fract<TYPE, SAFE> &b)
        {
            a *= b;
            return a;
        }

        // Divide
        constexpr Fract& operator/=(const Fract<TYPE, SAFE> &b)
        {
            N = N * b.D;
            D = D * b.N;
            simplify();
            return *this;
        }

        constexpr friend Fract operator/(Fract<TYPE, SAFE> a, const Fract<TYPE, SAFE> &b)
        {
            a /= b;
            return a;
        }

        // Less Than
        constexpr friend bool operator< (const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return (a.N*b.D < a.D*b.N);
        }

        // Greater Than Or Equal To
        constexpr friend bool operator>=(const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return !(a < b);
        }

        // Greater Than
        constexpr friend bool operator> (const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return (b < a);
        }

        // Less Than Or Equal To
        constexpr friend bool operator<=(const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return !(a > b);
        }

        // Equals
        constexpr friend bool operator==(const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return (a.N*b.D == a.D*b.N);
        }

        // Not Equals
        constexpr friend bool operator!=(const Fract<TYPE, SAFE> &a, const Fract<TYPE, SAFE> &b)
        {
            return !(a == b);
        }

        // Simplify Fraction
        constexpr void simplify()
        {
          #if safe
            if(D < 0){ D = -D; N = -N; } /// Numerator is what holds the sign
            const TYPE factor = GCD((N < 0) ? -N : N, D);
            N = N / factor; D = D / factor;
          #endif
        }

        template<class NUM_T>
        friend std::ostream& operator<<(std::ostream& os, const Fract<NUM_T, SAFE>& dt)
        {
          os << dt.N << "/" << dt.D;
          return os;
        }

    private:
        /** Background work **/
        // Greatest Common Factor
        constexpr TYPE GCD(const TYPE a, const TYPE b) const
        { return b == 0 ? a : GCD(b, a%b); }

        // Fucking ingenious work by me
        template<class NUM_T>
        void setNum(NUM_T num)
        {
          const bool negitive = num < 0;
          if(negitive){ num = -num; }

          #define MAX_ITER 4 // Iterations

          /*
           * GOING THROUGH ALL THIS EFFORT BECAUSE MAYBE
           * SOME DAY I MIGHT WANT TO USE A CHAR FOR A
           * FOR FUCK ALL REASONS
           */
          #define issigned(t) (((t)(-1)) < ((t) 0))
          #define umaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                              (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))
          #define smaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                              (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))
          #define maxof(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))
          #define MAX_DETAIL maxof(TYPE) // Maximum amount of precision before the data becomes useless

          TYPE iter = MAX_ITER, CFL[MAX_ITER]; // Continued Fraction List

          CFL[0] = TYPE(num);
          if(num == NUM_T(TYPE(num)))
          { N = num; D = 1; return; }
          num -= CFL[0];

          // Finding Numbers for List
          for(TYPE i = 1; i < iter; i++)
          {
            num = (num > 0) ? (1/num) : (-1/num);

            if(num > MAX_DETAIL)
            { iter = i; break; }

            CFL[i] = TYPE(num);
            num -= CFL[i];
          }

          // Solving Continued Fraction
          N = 0; D = 1;
          for(TYPE i = iter; i >= 0; i--)
          {
            TYPE nN = CFL[i] * N + D;
            D = N; N = nN;
            if(i == 0) { break; }
          }

          if(negitive){ N = -N; }
          return;
        }
};

#endif
