// P1387 最大正方形
// https://www.luogu.org/problemnew/show/P1387

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 102;

int n, m;
int M[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

int min3(int a, int b, int c)
{
    return min(min(a, b), c);
}

int main()
{
    int i, j;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            scanf("%d", &M[i][j]);

    dp[0][0] = M[0][0];
    for (i = 1; i < n; ++i)
        dp[i][0] = M[i][j] ? dp[i - 1][0] + 1 : 0;
    
    for (j = 1; j < m; ++j)
        dp[0][j] = M[i][j] ? dp[0][j - 1] + 1 : 0;
    
    int max_dp = 0;
    for (i = 1; i < n; ++i)
        for (j = 1; j < m; ++j)
        {
            if (M[i][j])
            {
                dp[i][j] = min3(dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]) + 1;
                max_dp = max(dp[i][j], max_dp);
            }
            else
                dp[i][j] = 0;
        }
    
    printf("%d", max_dp);
    printf("%d", max_dp);

    return 0;
}