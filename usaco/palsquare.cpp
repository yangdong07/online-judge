/*
ID: yesimim1
TASK: palsquare
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("palsquare.in", "r");
    FILE *fout = fopen ("palsquare.out", "w");

#include <fstream>
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");
*/

#include <cstdio>


char i2c[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int convert(int n, int base, char s[])
{
    int i = 0;
    for (int t = n; t; t /= base)
        s[i++] = i2c[t % base];
    s[i] = '\0';

    char c;
    for (int j = 0; j < i / 2; ++j)
        c = s[j], s[j] = s[i - j - 1], s[i - j - 1] = c;
    return i;
}


bool is_palindromic(char s[], int n)
{
    for (int i = 0; i < n / 2; ++i)
        if (s[i] != s[n - i - 1]) return false;
    
    return true;
}


int main()
{
    FILE *fin = fopen("palsquare.in", "r");
    FILE *fout = fopen("palsquare.out", "w");

    int base, len;
    char x[100], s[100];
    fscanf(fin, "%d", &base);

    for (int i = 1; i <= 300; ++i)
    {
        len = convert(i * i, base, s);
        if (is_palindromic(s, len))
        {
            convert(i, base, x);
            fprintf(fout, "%s %s\n", x, s);
        }
    }

    return 0;
}