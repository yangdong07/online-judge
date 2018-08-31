/*
ID: yesimim1
TASK: dualpal
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");
*/

#include <cstdio>

int convert(int n, int base, char *s)
{
    int i = 0;
    for (; n; n /= base)
        s[i++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n % base];
    s[i] = '\0';

    char c;
    for (int j = 0; j < i / 2; ++j)
        c = s[j], s[j] = s[i - j - 1], s[i - j - 1] = c;
    return i;
}


bool is_palindromic(char *s, int n)
{
    for (int i = 0; i < n / 2; ++i)
        if (s[i] != s[n - i - 1]) return false;
    return true;
}


bool is_dual_palindromic(int n, char *s)
{
    int count = 0, len;
    for (int base = 2; base <= 10; ++base)
    {
        len = convert(n, base, s);
        if (is_palindromic(s, len))
            count++;
        if (count >= 2)
            return true;
    }
    return false;
}


int main()
{
    FILE *fin = fopen ("dualpal.in", "r");
    FILE *fout = fopen ("dualpal.out", "w");

    int n, s;
    fscanf(fin, "%d%d", &n, &s);

    char num[10000];

    for (int i = 0; i < n; )
        if (is_dual_palindromic(++s, num))
        {
            fprintf(fout, "%d\n", s);
            ++i;
        }

    return 0;
}