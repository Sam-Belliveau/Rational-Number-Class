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
1. Integers:

`_Fract a = 1/3;` a = 0/1.  Integers round down when dividing

`_Fract b = 8/4;` b = 2/1.  It goes in perfectly

`_Fract c = 9/4;` c = 2/1.  The integer is rounded down

2. Floats:

`_Fract a = (double)1 / (double)3;` a = 3333/10000.  Floats can't represent 1/3 perfectly

`_Fract b = (double)8 / (double)4;` b = 2/1.         It goes in perfectly

`_Fract c = (double)9 / (double)4;` c = 9/4.         4 is a power of 2, so floats can represent it no problem

3. \_Fract:

`_Fract a = (_Fract)1 / (_Fract)3;` a = 1/3.  Because it is in a native format, no data is lost

`_Fract b = (_Fract)8 / (_Fract)4;` b = 2/1.  Because it is in a native format, no data is lost

`_Fract c = (_Fract)9 / (_Fract)4;` c = 9/4.  Because it is in a native format, no data is lost

__NOTE:__ 
_These problems are not caused by the \_Fract class, but because of the way floats and integers natively divide. \_Fract just reads what C++ outputs. Except for the last example, because it is handled by \_Fract, so it is lossless._
