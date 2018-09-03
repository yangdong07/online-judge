
// P1530 分数化小数 Fractions to Decimals
// https://www.luogu.org/problemnew/show/P1530

#include <cstdio>

const int MAX_N = 100001;

int position[MAX_N] = {0};
char decimal[MAX_N];

int divide(int a, int b)
{
    int i, j, t;
    i = sprintf(decimal, "%d", a / b);
    decimal[i++] = '.';

    a %= b;
    if (a == 0)
    {
        decimal[i++] = '0';
        decimal[i] = '\0';
        return i;
    }

    for (t = a; t && !position[t]; ++i, t %= b)
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

int main()
{
    int denominator, numerator;
    scanf("%d %d", &numerator, &denominator);

    divide(numerator, denominator);
    for (int i = 0; decimal[i]; ++i)
    {
        putchar(decimal[i]);
        if ((i + 1) % 76 == 0) putchar('\n');
    }
    return 0;
}