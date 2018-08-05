// P2077 红绿灯
// https://www.luogu.org/problemnew/show/P2077

#include <cstdio>

#define MAX_N 100001

int d[MAX_N], r[MAX_N], g[MAX_N];

int main()
{
    int n, m, i;

    scanf("%d %d", &n, &m);

    for (i = 1; i < n; ++i)
        scanf("%d", &d[i]);
    for (i = 1; i <= n; ++i)
        scanf("%d", &r[i]);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i]);
    
    int t = m;  // time passed
    int light;  // green - red time
    for (i = 1; i <= n; ++i)
    {
        light = t % (r[i] + g[i]);

        if (light > g[i]) // wait red
            t += (r[i] + g[i] - light);
        printf("%d\n", t);
        t += d[i];
    }
}