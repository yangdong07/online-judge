/*
ID: yesimim1
TASK: pprime
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("pprime.in", "r");
    FILE *fout = fopen ("pprime.out", "w");

#include <fstream>
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");
*/

#include <fstream>
#include <iostream>

using namespace std;

int a, b;
ofstream fout("pprime.out");
ifstream fin("pprime.in");

int is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
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
                    fout << p << endl;
            }
    }
    else if (digits == 2)
        if (a <= 11 && 11 <= b)
            fout << 11 << endl;
}


int main()
{

    fin >> a >> b;

    int ad = 0, bd = 0;
    for (int t = a; t; t /= 10) ++ad;
    for (int t = b; t; t /= 10) ++bd;

    // 1-digit number
    if (ad == 1)
    {
        for (int i = a; i < 10; ++i)
            if (is_prime(i))
                fout << i << endl;
        ad = 2;
    }

    // d-digits number
    for (int d = ad; d <= bd; ++d)
        prime_palindrome(d);
}