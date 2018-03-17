Rational Number Class
=====================

Operators so far:
-----------------

+, -, *, /, %, +=, -=, *=, /=, %=, !=, ==, >, <, >=, <=, =
    
The goal behind this project
----------------------------
1. Clean/Readable Code
2. Fast Code
3. Intuitive Usability
4. Following the standerd


Setting a Fraction Using:
-------------------------
1. __Integers:__

`Fract<long> a = 1/3;` __a = 0/1.__  _Integers round down when dividing_

`Fract<long> b = 8/4;` __b = 2/1.__  _It goes in perfectly_

`Fract<long> c = 9/4;` __c = 2/1.__  _The integer is rounded down_

2. __Floats:__

`Fract<long> a = (double)1 / (double)3;` __a = 1/3.__ _Using anti-primes, we can get great results_ __This used to equal 3333/10000__

`Fract<long> b = (double)8 / (double)4;` __b = 2/1.__ _It goes in perfectly_

`Fract<long> c = (double)9 / (double)4;` __c = 9/4.__ _4 is a power of 2, so floats can represent it no problem_

3. __Fract:__

`Fract<long> a = (_Fract)1 / (_Fract)3;` __a = 1/3.__ _Because it is in a native format, no data is lost_

`Fract<long> b = (_Fract)8 / (_Fract)4;` __b = 2/1.__ _Because it is in a native format, no data is lost_

`Fract<long> c = (_Fract)9 / (_Fract)4;` __c = 9/4.__ _Because it is in a native format, no data is lost_
