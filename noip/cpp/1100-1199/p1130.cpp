// P1130 红牌
// https://www.luogu.org/problemnew/show/P1130


#include <cstdio>
#include <algorithm>

#define MAX_M 2001
#define MAX_N 2001

int a[MAX_M][MAX_N];
using namespace std;

int read_int()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    
    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int main()
{
    int n, m, i, j;
    scanf("%d %d", &n, &m);

    for (i = 0; i < m; ++i)
        for (j = 0; j < n; ++j)
            a[i][j] = read_int();

    int dp[MAX_M] = {0};
    int tmp;
    for (j = 0; j < n; ++j)
    {
        tmp = min(dp[0], dp[m - 1]) + a[0][j];
        for (i = m - 1; i > 0; --i)
            dp[i] = min(dp[i], dp[i - 1]) + a[i][j];
        dp[0] = tmp;
        // printf("\n%d step: ", j + 1);
        // for (i = 0; i < m; ++i)
        //     printf("%d ", dp[i]);
    }
    
    int min_s = dp[0];
    for (i = 1; i < m; ++i)
        min_s = min(min_s, dp[i]);
    printf("%d", min_s);
        
    return 0;
}