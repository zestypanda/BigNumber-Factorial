# BigNumber-Factorial
BigNumber Factorial up to One Million

Class BigNumber is implemented using vector<unsigned long>, which is more than 2 times faster than vector<unsigned int>.

Three algorithms to calculate the factorial:
1) Brute Force
Sequentially multiply all numbers;
Runtime for n = 100,000: 
2) Prime Number
Convert the factorial to power of prime numbers;
For example, 11! = 2^8 * 3^4 * 5^2 * 7^1 * 11^1;
Run time for n = 100,000:
3) Split recursive
Convert to product of odd number sequence;
For example, 
11! = (1*3*5*7*9*11) * (2*4*6*8*10) 
= (1*3*5*7*9*11) * (1*2*3*4*5) * 2^5
= (1*3*5*7*9*11) * (1*3*5) * (2*4) * 2^5
= (1*3*5*7*9*11) * (1*3*5) * (1*2) * 2^7
Run time for n = 100,000:
