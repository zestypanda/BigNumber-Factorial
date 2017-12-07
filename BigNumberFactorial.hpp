#include <vector>

typedef unsigned long ulong;
typedef unsigned int uint;
class BigNumber {
public:
   friend BigNumber operator*(const BigNumber& lh, const BigNumber& rh);
   friend BigNumber power(const BigNumber& num, uint k);
   explicit BigNumber(ulong val = 0);
   BigNumber& operator*= (const BigNumber& rh);
   BigNumber& operator*= (ulong rh);
   BigNumber& operator+= (ulong rh);
   void print();
   std::string toString();
private:
   // 9 digits saved in each element, from least significant bits
   // for example, n = 121212 003412341 123456789
   // num = {123456789, 3412341, 121212};
   std::vector<ulong> num;
};

BigNumber operator*(const BigNumber& lh, const BigNumber& rh);
BigNumber power(const BigNumber& num, uint k);
BigNumber power(const uint num, uint k);
BigNumber factorialBruteForce (uint n);
BigNumber factorialPrimeNumber (uint n);
BigNumber factorialSplitRecursive (uint n);
int nMinusSumofBits(int n);