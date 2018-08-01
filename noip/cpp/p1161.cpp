// P1161 开灯
// https://www.luogu.org/problemnew/show/P1161

#include <cstdio>


int main()
{
    int n, t, lamps=0;
    double a;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf %d", &a, &t);
        for (int j = 1; j <= t; ++j)
            lamps ^= int(a * j);
    }
    printf("%d", lamps);
}