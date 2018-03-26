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

Unique feature
--------------
This is the only class that supports NATIVE floating point translations to readable fractions. It takes pi and outputs 377/120 `the standard approximation is 355/113 but it's a pretty good guess`, it take root2 and gives you 99/70 `Which is often the abbreviation of root2 when in fractional notation`, this is some of the best AUTOMATED translations I have ever seen. Sure, there are better fractions, but this is automatic, something you don't have to worry about, meaning that you're getting some of the best accuracies when formatting floats. This is caused by the fact that we simplify with [anti-primes](https://en.wikipedia.org/wiki/Highly_composite_number), the number we use is [5040](https://en.wikipedia.org/wiki/5040_(number)) because it is the most useful, smaller ones don't give good results, bigger ones cause overflows.


TODO:
-----

- More optimized simplifications built into the opperators
- Native interaction with std::math librarys
- Native interaction with streams
