// P1164 小A点菜
// https://www.luogu.org/problemnew/show/P1164


#include <cstdio>

int main()
{
    const int MAX_M = 10001;

    int n, m, price;
    int dp[MAX_M] = { 0 };
    scanf("%d %d", &n, &m);

    int i, j;
    dp[0] = 1;  // 一分钱都没有的方案有一个： 什么都不点。

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &price);
        for (j = m; j >= price; --j)
            dp[j] += dp[j - price];
    }
    printf("%d", dp[m]);

    return 0;
}