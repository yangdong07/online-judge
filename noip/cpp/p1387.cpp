// P1387 最大正方形
// https://www.luogu.org/problemnew/show/P1387

#include <cstdio>


int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int min3(int a, int b, int c) { return min(min(a, b), c); }

int main()
{
    const int MAX_N = 102;
    int n, m, i, j;
    int M[MAX_N][MAX_N];
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%d", &M[i][j]);

    int max_dp = 0;
    int dp[MAX_N][MAX_N] = { 0 };
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
        {
            if (M[i][j])
            {
                dp[i][j] = min3(dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]) + 1;
                max_dp = max(max_dp, dp[i][j]);
            }
            else
                dp[i][j] = 0;
        }
    
    printf("%d", max_dp);

    return 0;
}