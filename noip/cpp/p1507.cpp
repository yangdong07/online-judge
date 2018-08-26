// P1507 NASA的食物计划
// https://www.luogu.org/problemnew/show/P1507

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_W = 401;
    const int MAX_V = 401;
    int n, W, V;

    scanf("%d %d %d", &V, &W, &n);

    int wi, vi, w, v, ci;
    int dp[MAX_W][MAX_V] = {0};

    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d %d", &vi, &wi, &ci);
        for (w = W; w >= wi; --w)
            for (v = V; v >= vi; --v)
                dp[w][v] = max(dp[w][v], dp[w - wi][v - vi] + ci);
    }

    printf("%d", dp[W][V]);

    return 0;
}