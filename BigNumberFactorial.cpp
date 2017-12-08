#include "BigNumberFactorial.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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

inline int BigNumber::size() {
    return num.size();
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
    vector<pair<int, int>> primes; // pairs of prime and counts
    for (int i = 2; i <= n; i++) {
        if (mp[i] == 0) {
            for (int j = i*2; j <= n; j += i)
                mp[j] = 1;
            uint j = n, cnt = 0;
            while (j) {
                j /= i;
                cnt += j;
            }
            primes.push_back({i, cnt});
        }
    }
    int m = primes.size();
    BigNumber ans(1);
    vector<BigNumber> product;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = m-1; i >= 0; --i) {
        product.push_back(move(power(primes[i].first, primes[i].second)));
        pq.push({product[m-1-i].size(), m-1-i});
    }
    // optimization: multiply small numbers first, using priority queue
    while (pq.size() > 1) {
        int p1 = pq.top().second;
        pq.pop();
        int p2 = pq.top().second;
        pq.pop();
        product[p1] *= product[p2];
        pq.push({product[p1].size(), p1});
    }
    return product[pq.top().second];
}


BigNumber factorialSplitRecursive(uint n){
    BigNumber ans(1);
    stack<uint> sk;
    // All ending numbers in the odd sequences
    uint m = n;
    while (n > 2) {
        sk.push(n - 1 + (n&1));
        n >>= 1;
    }
    BigNumber oddSeq(1);
    int cur = 1;
    while (!sk.empty()) {
        uint k = sk.top();
        sk.pop();
        // Merge style product is more efficient than sequential
        oddSeq *= partProduct(cur, k);
        ans *= oddSeq;
        cur = k+2;
    }
    return ans*power(2, nMinusSumofBits(m));
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

BigNumber factorialSplitRecursiveTwo(uint n) {  
    BigNumber p(1), r(1);
    loop(n, p, r);
    return r*power(2, nMinusSumofBits(n));
}
 
void loop(uint n, BigNumber& p, BigNumber& r) {
    if (n <= 2) return;
    loop(n/2, p, r);
    p *= partProduct(n/2 + 1 + ((n/2)&1), n -1 + (n&1));
    // Merge style product is more efficient than sequential
    /*BigNumber tmp(1);
    for (int i = n/2 + 1 + ((n/2)&1); i <= n -1 + (n&1); i += 2)
        tmp *= i;
    p *= tmp;*/
    r *= p;
}

BigNumber partProduct(uint n, uint m) {
    if (m == n) return BigNumber(n);
    uint k = (n+m)>>1;
    k = k -1 + (k&1);
    return partProduct(n, k)*partProduct(k+2, m);
}