/*
ID: yesimim1
TASK: fracdec
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("fracdec.out");
    ifstream fin ("fracdec.in");
*/

#include <cstdio>

FILE *fin = fopen("fracdec.in", "r");
FILE *fout = fopen("fracdec.out", "w");

const int MAX_N = 100001;

int position[MAX_N] = {0};
char decimal[MAX_N];

int divide(int a, int b)
{
    decimal[0] = '.';
    if (a == 0)
    {
        decimal[1] = '0';
        decimal[2] = '\0';
        return 2;
    }

    int i, j, t;
    for (i = 1, t = a; t && !position[t]; ++i, t %= b)
    {
        position[t] = i;
        t *= 10;
        decimal[i] = '0' + t / b;
    }
    if (t)
    {
        for (j = i; j > position[t]; --j)
            decimal[j] = decimal[j - 1];
        decimal[j] = '(';
        decimal[++i] = ')';
        ++i;
    }
    decimal[i] = '\0';
    return i;
}

void print_decimal(int integer)
{
    int i = 2, j;
    fprintf(fout, "%d", integer);
    for (integer /= 10; integer; integer /= 10, ++i);

    for (j = 0; decimal[j]; ++j, ++i)
    {
        fputc(decimal[j], fout);
        if (i % 76 == 0) fputc('\n', fout);
    }
    fputc('\n', fout);
    
}

int main()
{
    int denominator, numerator;
    fscanf(fin, "%d %d", &numerator, &denominator);

    divide(numerator % denominator, denominator);
    print_decimal(numerator / denominator);
    return 0;
}