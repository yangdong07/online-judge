// P1424 小鱼的航程(改进版)
// https://www.luogu.org/problemnew/show/P1424

#include <cstdio>

int main()
{
    int x, n, i;
    int swim[7] = { 250, 250, 250, 250, 250, 250, 250 };
    scanf("%d %d", &x, &n);

    swim[(7 - x) % 7] = 0;  // sunday
    swim[(13 - x) % 7] = 0; // saturday

    int km = (n / 7) * 1250;

    for (i = 0; i < n % 7; i++)
        km += swim[i];
    printf("%d", km);
}