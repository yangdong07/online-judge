// P1006 传纸条
// https://www.luogu.org/problemnew/show/P1006

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 51;
    int m, n, i, j;
    int a[MAX_N][MAX_N];
    int dp[MAX_N][MAX_N][MAX_N] = {0};

    scanf("%d %d", &m, &n);

    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);

    int r, c, d;
    int max_s;
    for (r = 2; r <= m; ++r)
    {
        for (d = r - 1; d > 0; --d)
            for (c = 1; c <= n - d; ++c)
            {
                max_s = dp[r][c - 1][d];                 // left, d
                max_s = max(max_s, dp[r][c - 1][d + 1]); // left, d + 1
                max_s = max(max_s, dp[r - 1][c][d]);     // up, d
                max_s = max(max_s, dp[r - 1][c][d - 1]); // up, d + 1
                dp[r][c][d] = max_s + a[r][c] + a[r - d][c + d];
            }
    }
    printf("%d", dp[m][n - 1][1]);

    return 0;
}