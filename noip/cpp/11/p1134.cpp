
// P1134 阶乘问题
// https://www.luogu.org/problemnew/show/P1134



#include <cstdio>

int main()
{
    int n, i;
    scanf("%d", &n);

    // n = 9999;
    // n = 50000000;
    int _power8[] = {1, 8, 4, 2, 6};

    int ans = 1, n_eights = 0;
    while (n)
    {
        for (i = 1; i <= n % 5; ++i)
            ans *= i;
        n /= 5;
        if (n & 1) ans = (ans * 4) % 10;
        n_eights += n;
    }

    if (n_eights) ans *= _power8[(n_eights - 1) % 4 + 1];
    printf("%d\n", ans % 10);

    return 0;
}