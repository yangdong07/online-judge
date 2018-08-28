// P1510 精卫填海
// https://www.luogu.org/problemnew/show/P1510

#include <cstdio>

int max(int a, int b) { return (a > b) ? a : b; }

int main()
{
    const int MAX_W = 10001;
    int V, n, W;
    scanf("%d %d %d", &V, &n, &W);

    int vi, wi, i, w;
    int dp[MAX_W] = {0};
    for (i = 1; i <= n; ++i)
    {
        scanf("%d %d", &vi, &wi);
        for (w = W; w >= wi; --w)
            dp[w] = max(dp[w], dp[w - wi] + vi);
    }

    for (w = 1; w <= W; ++w)
    {
        // printf("%d ", dp[w]);
        if (dp[w] >= V)
        {
            printf("%d", W - w);
            return 0;
        }
    }
    printf("Impossible");
    return 0;
}