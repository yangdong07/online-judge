
// P2733 家的范围 Home on the Range
// https://www.luogu.org/problemnew/show/P2733

#include <cstdio>


int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int min3(int a, int b, int c) { return min(min(a, b), c); }

int read_digit()
{
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    return c - '0';
}

int main()
{
    const int MAX_N = 250 + 1;
    int n, i, j, k;
    int map[MAX_N][MAX_N];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            map[i][j] = read_digit();

    int dp[MAX_N][MAX_N] = { 0 };
    int max_dp = 0;
    int count[MAX_N] = { 0 };
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
        {
            if (map[i][j])
            {
                dp[i][j] = min3(dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]) + 1;
                for (k = 2; k <= dp[i][j]; ++k)
                    ++count[k];
                max_dp = max(max_dp, dp[i][j]);
            }
            else
                dp[i][j] = 0;
        }
    
    for (k = 2; k <= max_dp; ++k)
        printf("%d %d\n", k, count[k]);

    return 0;
}