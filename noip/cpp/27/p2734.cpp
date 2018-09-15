
// P2734 游戏 A Game
// https://www.luogu.org/problemnew/show/P2734

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 200 + 1;
    int n, i;
    int a[MAX_N], sum[MAX_N] = {0};

    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    int dp[MAX_N + 1] = {0};  // dp(i, k) ~ [i, i + k]

    for (int k = 0; k < n; ++k)
        for (i = 1; i + k <= n; ++i)
            dp[i] = sum[i + k] - sum[i - 1] - min(dp[i], dp[i + 1]);
    
    // for (i = 0; i <= n; ++i)
    //     printf("%d ", dp[i]);
    // printf("\n");

    printf("%d %d\n", dp[1], sum[n] - dp[1]);


    return 0;
}