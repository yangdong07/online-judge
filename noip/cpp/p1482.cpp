// P1482 Cantor表（升级版）
// https://www.luogu.org/problemnew/show/P1482

#include <cstdio>

int gcd(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;

    if (a == b)
        return a;

    if (a > b)
        return gcd(a - b, b);

    return gcd(a, b - a);
}

int main()
{
    int a1, a2, b1, b2;
    scanf("%d/%d %d/%d", &a1, &a2, &b1, &b2);
    int c1 = a1 * b1, c2 = a2 * b2;
    int c = gcd(c1, c2);
    printf("%d %d", c2 / c, c1 / c);
}