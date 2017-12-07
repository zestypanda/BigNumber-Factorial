#include "BigNumberFactorial.hpp"
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int main() {
   cout << "Please input a non-negative number (<= 1000000): \n";
   int n;
   cin >> n;
   if (n < 0 || n > 1000000) {
      cout << "invalid input\n";
      exit(1);
   }
   // using Best Split Recursive
   time_t t1, t2;
   time(&t1);
   BigNumber ans = factorialSplitRecursive(n);
   //BigNumber ans = factorialBruteForce(n);
   //BigNumber ans = factorialPrimeNumber(n);
   time(&t2);
   cout << ans.toString() << '\n';
   cout << "Total run time: " << difftime(t2,t1) << "s\n";
   
   /*// Comparing three algorithms
   
   vector<string> results(3);
   vector<int> runtime(3);
   for (int i = 0; i < 3; i++) {
       time_t t1, t2;
       BigNumber ans;
       if (i == 0) {
          time(&t1);
          ans = factorialBruteForce(n);
          time(&t2);
       }
       else if (i == 1) {
          time(&t1);
          ans = factorialPrimeNumber(n);
          time(&t2);
       }
       else {
          time(&t1);
          ans = factorialSplitRecursive(n);
          time(&t2);
       }
       results[i] = ans.toString();
       runtime[i] = difftime(t2,t1);
   }
   for (int i = 1; i < 3; i++) {
       if (results[i] != results[0]) {
           cout << "Wrong answer!\n";
           exit(1);
        }
   }
   cout << results[0] << '\n';
   cout << "Passed Test\n";
   cout << "Total run time\n";
   cout << "Brute Force: " << runtime[0] << "s\n";
   cout << "Prime Number: " << runtime[1] << "s\n";
   cout << "Split Recursive: " << runtime[2] << "s\n";  
   */
}