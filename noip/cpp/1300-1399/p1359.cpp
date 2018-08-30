// P1359 租用游艇
// https://www.luogu.org/problemnew/show/P1359

#include <cstdio>

#define MAX_N 201

int min(int a, int b) { return a < b ? a : b; }

const int MAX_INT = 1 << 30;

int main()
{
    int n, i, j;
    scanf("%d", &n);

    int r[MAX_N][MAX_N];

    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n; ++j)
            scanf("%d", &r[i][j]);
    
    int dp[MAX_N] = {0};
    int min_r;
    for (i = n - 2; i >= 0; --i)
    {
        min_r = MAX_INT;
        for (j = i + 1; j < n; ++j)
            min_r = min(min_r, dp[j] + r[i][j]);
        dp[i] = min_r;
    }

    printf("%d", dp[0]);

    return 0;
}