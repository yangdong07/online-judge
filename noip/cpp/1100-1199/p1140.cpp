// P1140 相似基因
// https://www.luogu.org/problemnew/show/P1140

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max(a, max(b, c)); }

int _similarity[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}};

int gci(char c)
{
    switch(c)
    {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return 4;
    }
}

int similarity(char c1, char c2)
{
    return _similarity[gci(c1)][gci(c2)];
}

int main()
{
    const int MAX_N = 101;
    int n, m, i, j;
    char g1[MAX_N], g2[MAX_N];
    scanf("%d %s\n%d %s", &n, g1, &m, g2);

    int dp[MAX_N][MAX_N];

    dp[0][0] = 0;
    for (i = 1; i <= n; ++i)
        dp[i][0] = dp[i - 1][0] + similarity(g1[i - 1], '-');
    for (j = 1; j <= m; ++j)
        dp[0][j] = dp[0][j - 1] + similarity('-', g2[j - 1]);

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
        {
            dp[i][j] = max3(
                dp[i][j - 1] + similarity('-', g2[j - 1]),
                dp[i - 1][j] + similarity(g1[i - 1], '-'),
                dp[i - 1][j - 1] + similarity(g1[i - 1], g2[j - 1]));
        }

    // for (i = 0; i <= n; ++i)
    // {
    //     for (j = 0; j <= m; ++j)
    //         printf("%3d ", dp[i][j]);
    //     printf("\n");
    // }
    printf("%d", dp[n][m]);
    return 0;
}