// P1498 南蛮图腾
// https://www.luogu.org/problemnew/show/P1498

#include <cstdio>

int main()
{
    int n, i, j;
    int a[1030] = {1};

    scanf("%d", &n);

    n = (1 << n);

    for (j = 0; j <= n; ++j)
        a[j] = 1;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n - i - 1; ++j)
            putchar(' ');
        for (j = i - 1; j > 0; --j)
            a[j] ^= a[j - 1];
        if (i % 2 == 0)
            for (j = 0; j <= i; ++j)
                printf(a[j] ? "/\\" : "  "); //奇数行
        else
            for (j = 0; j <= i; j += 2)
                printf(a[j] ? "/__\\" : "    "); //偶数行
        printf("\n");
    }
    return 0;
}