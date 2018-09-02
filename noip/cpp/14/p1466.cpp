
// P1466 集合 Subset Sums
// https://www.luogu.org/problemnew/show/P1466

#include <cstdio>

int main()
{
    const int MAX_SUM = 40 * 39 / 2;
    int n;
    scanf("%d", &n);
    int sum = (n + 1) * n / 2;
    if (sum & 1)
    {
        printf("0\n");
        return 0;
    }
    sum /= 2;
    long long dp[MAX_SUM] = {0};

    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int s = sum; s >= i; --s)
            dp[s] += dp[s - i];
        
        // printf("dp(%d, w): ", i);
        // for (int s = 1; s <= sum; ++s)
        //     printf("%d ", dp[s]);
        // printf("\n");
    }
    
    printf("%lld", dp[sum] / 2);

    return 0;
}