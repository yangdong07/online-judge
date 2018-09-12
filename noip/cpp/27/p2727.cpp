
// P2727 01串 Stringsobits
// https://www.luogu.org/problemnew/show/P2727

#include <cstdio>


const int MAX_N = 31 + 1;

unsigned dp[MAX_N][MAX_N];


void dfs_print(int n, int l, int k)
{
    // printf("%d %d %d %d: ", n, l, k, dp[n][l]);
    if (n == 0) return;
    if (k <= dp[n - 1][l])  // 0
    {
        putchar('0');
        dfs_print(n - 1, l, k);
    }
    else
    {
        putchar('1');
        dfs_print(n - 1, l - 1, k - dp[n - 1][l]);
    }
}

int main()
{
    int n, l, k, i, j;
    scanf("%d %d %d", &n, &l, &k);

    for (i = 0; i <= n; ++i)
        dp[0][i] = dp[i][0] = 1;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

    // for (i = 0; i <= n; ++i)
    // {
    //     for (j = 0; j <= n; ++j)
    //         printf("%-3u ", dp[i][j]);
    //     printf("\n");
    // }
    
    dfs_print(n, l, k);

    printf("\n");
    
    return 0;
}