Rational Number Class
=====================

Operators so far:
-----------------

+, -, *, /, %, +=, -=, *=, /=, %=, ==, >, <, >=, <=, =
    
The goal behind this project
----------------------------
1. Clean/Readable Code
2. Fast Code
3. Intuitive Usability
4. Following the standerd


Setting a Fraction Using:
-------------------------
1. __Integers:__

`_Fract a = 1/3;` __a = 0/1.__  _Integers round down when dividing_

`_Fract b = 8/4;` __b = 2/1.__  _It goes in perfectly_

`_Fract c = 9/4;` __c = 2/1.__  _The integer is rounded down_

2. __Floats:__

`_Fract a = (double)1 / (double)3;` __a = 3333/10000.__  _Floats can't represent 1/3 perfectly_

`_Fract b = (double)8 / (double)4;` __b = 2/1.__         _It goes in perfectly_

`_Fract c = (double)9 / (double)4;` __c = 9/4.__         _4 is a power of 2, so floats can represent it no problem_

3. __\_Fract:__

`_Fract a = (_Fract)1 / (_Fract)3;` __a = 1/3.__  _Because it is in a native format, no data is lost_

`_Fract b = (_Fract)8 / (_Fract)4;` __b = 2/1.__  _Because it is in a native format, no data is lost_

`_Fract c = (_Fract)9 / (_Fract)4;` __c = 9/4.__  _Because it is in a native format, no data is lost_

__NOTE:__ 
_These problems are not caused by the \_Fract class, but because of the way floats and integers natively divide. \_Fract just reads what C++ outputs. Except for the last example, because it is handled by \_Fract, so it is lossless._
