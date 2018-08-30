// P2192 HXY玩卡片
// https://www.luogu.org/problemnew/show/P2192

#include <cstdio>

int main()
{
    int n, i, d;
    int zeros = 0, fives = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &d);
        if (d == 5) fives++;
        else if (d == 0) zeros++;
    }

    if (zeros == 0)
    {
        printf("-1");
        return 0;
    }

    if (fives < 9)
    {
        printf("0");
        return 0;
    }

    while (fives >= 9)
    {
        printf("555555555");
        fives -= 9;
    }

    for (i = 0; i < zeros; ++i)
        putchar('0');
}