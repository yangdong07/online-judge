
// P2735 电网 Electric Fences
// https://www.luogu.org/problemnew/show/P2735

#include <cstdio>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int main()
{
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);

    int b;
    b = gcd(n, m) + gcd(m, p > n ? p - n : n - p) + p;
    printf("%d\n", p * m / 2 - b / 2 + 1);
    return 0;
}