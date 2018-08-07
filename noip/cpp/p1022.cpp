// P1022 计算器的改良
// https://www.luogu.org/problemnew/show/P1022


#include <cstdio>
#include <cstring>
#include <cctype>

#define MAX_N 65536

// parse left or right
char parse(char *s, int n, int *pa, int *pb)
{
    int i = 0, sign = 1;
    int d = 0;
    char c;

    if (s[0] == '-')
    {
        sign = -1;
        i = 1;
    }

    for ( ; i < n; ++i)
    {
        if (isdigit(s[i]))
        {
            d = d * 10 + s[i] - '0';
            continue;
        }

        if (isalpha(s[i]))  // x
        {
            c = s[i];
            *pa += (sign * (d == 0 ? 1 : d));
            sign = 1;
        }
        else
        {
            *pb += (sign * d);
            sign = s[i] == '+' ? 1 : -1;
        }
        d = 0;
    }
    return c;
}

int main()
{
    char s[MAX_N];

    scanf("%s", s);

    int n = strlen(s);
    s[n] = '=';

    int a1 = 0, b1 = 0, a2 = 0, b2 = 0;

    int i = 0;
    while (s[i++] != '=');

    char c;
    c = parse(s, i, &a1, &b1);
    c = parse(s + i, n + 1, &a2, &b2);
    // printf("%d x + %d = %d x + %d", a1, b1, a2, b2);

    printf("%c=%.3f", c, b2 == b1 ? 0.0 : 1.0 * (b2 - b1) / (a1 - a2));
}