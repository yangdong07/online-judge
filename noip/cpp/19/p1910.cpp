// P1910 L国的战斗之间谍
// https://www.luogu.org/problemnew/show/P1910

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_W = 1001;
    const int MAX_V = 1001;
    int n, W, V;

    scanf("%d %d %d", &n, &W, &V);

    int wi, vi, w, v, ci;
    int dp[MAX_W][MAX_V] = {0};

    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d %d", &ci, &wi, &vi);
        for (w = W; w >= wi; --w)
            for (v = V; v >= vi; --v)
                dp[w][v] = max(dp[w][v], dp[w - wi][v - vi] + ci);
    }

    printf("%d", dp[W][V]);

    return 0;
}