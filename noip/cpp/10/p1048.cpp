// P1048 采药
// https://www.luogu.org/problemnew/show/P1048

#include <cstdio>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    const int MAX_W = 1001;
    int n, W;
    scanf("%d %d", &W, &n);

    int v, w;
    int dp[MAX_W] = { 0 };
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d %d", &w, &v);
        for (int j = W; j > 0; --j)
            if (j >= w)
                dp[j] = max(dp[j], dp[j - w] + v);
    }
    printf("%d", dp[W]);

    return 0;
}