
// P1796 汤姆斯的天堂梦_NOI导刊2010提高（05）
// https://www.luogu.org/problemnew/show/P1796

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 100 + 1;
    const int MAX_M = 100 + 1;
    const int INF = 1000 * 100 * 10;

    int n, m, i, j, k;
    int dp[MAX_N][MAX_M];

    scanf("%d", &n);

    dp[0][1] = 0;  // where toms stay
    int cost;
    for (k = 1; k <= n; ++k)
    {
        scanf("%d", &m);
        for (i = 1; i <= m; ++i)
        {
            dp[k][i] = INF;
            for (scanf("%d", &j); j; scanf("%d", &j))
            {
                scanf("%d", &cost);
                dp[k][i] = min(dp[k][i], dp[k - 1][j] + cost);
            }
        }
    }
    int min_cost = INF;
    for (j = 1; j <= m; ++j)
        min_cost = min(min_cost, dp[n][j]);
    printf("%d\n", min_cost);
    return 0;
}