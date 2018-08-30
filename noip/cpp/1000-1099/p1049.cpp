// P1049 装箱问题
// https://www.luogu.org/problemnew/show/P1049

#include <cstdio>

#define MAX_V 20001

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int V, n, v;
    scanf("%d%d", &V, &n);

    int dp[MAX_V] = { 0 };
    int i, j;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &v);
        for (j = V; j > 0; --j)
            if (j >= v)
                dp[j] = max(dp[j], dp[j - v] + v);
    }
    printf("%d", V - dp[V]);

    return 0;
}