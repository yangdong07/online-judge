// P1217 [USACO1.5]回文质数 Prime Palindromes
// https://www.luogu.org/problemnew/show/P1217


#include <iostream>
#include <cmath>

using namespace std;

int a, b;

int is_prime(int n)
{
    for (int i = 2; i < int(sqrt(n) + 1); ++i)
        if (n % i == 0) return false;
    return true;
}

int palindrome(int n, int m)
{
    int p = n;

    if (m != -1) p = p * 10 + m;

    for (int t = n; t; t /= 10)
        p = p * 10 + t % 10;
    return p;
}

void prime_palindrome(int digits)
{
    if (digits > 7) return;

    int n = 1, p;
    for (int i = 0; i < digits / 2; ++i) n *= 10;
    if (digits & 1) // odd
    {
        for (int i = n / 10; i < n; ++i)
            for (int j = 0; j < 10; ++j)
            {
                p = palindrome(i, j);
                if (is_prime(p) && p >= a && p <= b)
                    cout << p << endl;
            }
    }
    else if (digits == 2)
        if (a <= 11 && 11 <= b)
            cout << 11 << endl;
}


int main()
{
    cin >> a >> b;

    int ad = 0, bd = 0;
    for (int t = a; t; t /= 10) ++ad;
    for (int t = b; t; t /= 10) ++bd;

    // 1-digit number
    if (ad == 1)
    {
        for (int i = a; i < 10; ++i)
            if (is_prime(i))
                cout << i << endl;
        ad = 2;
    }

    // d-digits number
    for (int d = ad; d <= bd; ++d)
        prime_palindrome(d);
}