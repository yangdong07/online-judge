// P1017 进制转换
// https://www.luogu.org/problemnew/show/P1017

#include <cstdio>


int main()
{
    const int MAX_N = 10000;
    char digits[50];
    char s[MAX_N];

    int n, base;
    scanf("%d %d", &n, &base);

    int i;
    for (i = 0; i < 10; ++i)
        digits[i] = '0' + i;
    for (i = 10; i < 36; ++i)
        digits[i] = 'A' + i - 10;

    int k = 0;
    int pbase = base < 0 ? -base : base;
    for (int r, t = n; t; t /= base)
    {
        r = t % base;
        if (r < 0)
        {
            r += pbase;
            t -= pbase;
        }
        s[k++] = digits[r];
        // printf("%d %d\n", r, t);
    }

    printf("%d=", n);
    for (i = k - 1; i >= 0; --i)
        putchar(s[i]);
    printf("(base%d)", base);
    return 0;
}