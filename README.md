# FiboSystem
Representing numbers in Fibonnaci base, where first two elements ((0, 1)) of the fibonacci sequence are not considered.
Main focus was on the move semantics and temporary objects in C++.

The digit of the Fibonacci system is called fibit. A normalized representation is such a state, in which there are no two ones next to each other in the representation.

Only positive numbers are considered to be represented in fibonacci system.

Fibo f1      - creates number 0

Fibo f1(str) - creates number based on string, which is the representation of a number in fibonacci system.

Fibo(n)      - creates number equal to n

Fibo f1(f2)  - copy constructor

f1 = f2 - assignment

f1 + f2 - addition of numbers in fibonacci system

f1 & f2 - bitwise AND operator on fibits (Normalized representation)

f1 | f2 - bitwise OR (Normalized representation)

f1 ^ f2 - bitwise XOR (Normalized representation)

f1 << n  - shift fibits n positions to left 

f1 += f2

f1 &= f2

f1 |= f2

f1 ^= f2

f1 <<= n

f1 op f2 - comparator operators for two numbers represented in f1 and f2,
           where op is one of these operators: ==, <, <=, != , >, >=

os << f1 - prints f1 on the output stream without white chars and in normalized representation

f1.length() - returns size of the representation in normalized representation.

Zero() and One() return object representing numbers 0 and 1. Objects are immutable.
