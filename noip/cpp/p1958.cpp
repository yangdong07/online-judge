// P1958 上学路线_NOI导刊2009普及（6）
// https://www.luogu.org/problemnew/show/P1958


#include <cstdio>

#define MAX_N 41

int main()
{
    int n, m, k, i, j;
    scanf("%d%d%d", &n, &m, &k);

    int x, y;
    int map[MAX_N][MAX_N] = {0};
    int dp[MAX_N][MAX_N] = {0};
    for (i = 0; i < k; ++i)
    {
        scanf("%d%d", &x, &y);
        map[x][y] = 1;
    }
    // for (i = 1; i <= n; ++i)
    // {
    //     for (j = 1; j <= m; ++j)
    //         printf("%d ", map[i][j]);
    //     printf("\n");
    // }

    dp[0][1] = 1;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            if (map[i][j] == 0)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

    printf("%d", dp[n][m]);

    return 0;
}