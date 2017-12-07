#include "BigNumberFactorial.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#include <cmath>
using namespace std;

const ulong N = 1000000000;
//BigNumber currentN(1);

BigNumber::BigNumber(ulong val){
    while (val) {
        num.push_back(val% N);
        val /= N;
    }
}

BigNumber& BigNumber::operator*= (const BigNumber& rh) {
    BigNumber ans = (*this)*rh;
    swap(num, ans.num);
    return *this;
}

BigNumber& BigNumber::operator*= (ulong rh) {
    int n = num.size();
    ulong carry = 0;
    for (int i = 0; i < n; i++) {
        num[i] *= rh;
        num[i] += carry;
        carry = num[i]/N;
        num[i] %= N;
    }
    if (carry) num.push_back(carry);
    return *this;
}

BigNumber& BigNumber::operator+= (ulong rh) {
    int n = num.size();
    for (int i = 0; i < n && rh != 0; i++) {
        num[i] += rh;
        rh = num[i]/N;
        num[i] %= N;
    }
    if (rh) num.push_back(rh);
    return *this;
}

void BigNumber::print() {
    cout << "The answer is: \n"; 
    cout << this->toString() << '\n';
}

string BigNumber::toString(){
    int n = num.size();
    if (n == 0) return "0";
    string s;
    for (int i = n-1; i >= 0; i--) {
        string t = to_string(num[i]);
        if (i != n-1) s += string(9-t.size(), '0');
        s += t;
    }
    return s;
}

BigNumber operator*(const BigNumber& lh, const BigNumber& rh) {
    int n1 = lh.num.size(), n2 = rh.num.size();
    vector<ulong> ans(n1+n2, 0);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            int k = i+j;
            ans[k] += lh.num[i]*rh.num[j];
            while (ans[k] > N*N) {
                ans[k+1] += ans[k]/N;
                ans[k++] %= N;
            } 
        }
    }
    for (int i = 0; i < n1+n2-1; i++) {
         ans[i+1] += ans[i]/N;
         ans[i] %= N;
    }
    while (ans.back() == 0) ans.pop_back();
    BigNumber res;
    swap(res.num, ans);
    return res;
}

BigNumber power(const uint num, uint k) {
    string s;
    while (k) {
       s += (k&1) + '0';
       k >>= 1;
    }
    reverse(s.begin(), s.end());
    BigNumber ans(1);
    for (char c:s) {
       ans *= ans;
       if (c == '1') ans *= num;
    }
    return ans;    
}

BigNumber power(const BigNumber& num, uint k) {
    string s;
    while (k) {
       s += (k&1) + '0';
       k >>= 1;
    }
    reverse(s.begin(), s.end());
    BigNumber ans(1);
    for (char c:s) {
       ans *= ans;
       if (c == '1') ans *= num;
    }
    return ans;    
}

BigNumber factorialBruteForce(uint n){
    BigNumber ans(1);
    for (int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}

BigNumber factorialPrimeNumber(uint n) {
    vector<int> mp(n+1, 0);
    vector<pair<int, int>> primes;
    for (int i = 2; i <= n; i++) {
        if (mp[i] == 0) {
            primes.push_back({i, 0});
            for (int j = i*2; j <= n; j += i)
                mp[j] = 1;
        }
    }
    int m = primes.size();
    for (int i = 2; i <= n; i++) {
        int val = i;
        for (int j = 0; j < m && val != 1; ++j) {
            while (val%primes[j].first == 0) {
                primes[j].second++;
                val /= primes[j].first;
            }
        }
    }
    BigNumber ans(1);
    for (auto& p:primes) 
        ans *= power(p.first, p.second); 
    return ans;
}

BigNumber factorialSplitRecursive(uint n){
    BigNumber ans = power(2, nMinusSumofBits(n));
    stack<uint> sk;
    // All ending numbers in the odd sequences
    while (n > 2) {
        sk.push(n - 1 + (n&1));
        n >>= 1;
    }
    BigNumber oddSeq(1);
    int cur = 1;
    while (!sk.empty()) {
        uint k = sk.top();
        sk.pop();
        for (; cur <= k; cur += 2)
            oddSeq *= cur;
        ans *= oddSeq;
    }
    return ans;
}

// power of 2 in n!
int nMinusSumofBits(int n){
    int m = n;
    while (m) {
        n--;
        m &= m-1;
    }
    return n;
}
