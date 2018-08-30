// P2347 砝码称重
// https://www.luogu.org/problemnew/show/P2347

#include <cstdio>

#define MAX_WEIGHT 1001
#define MAX_N 6

/* solution 1, knapsack */

int wi[MAX_N] = {1, 2, 3, 5, 10, 20};
int wc[MAX_N];

int main()
{
    int i, j;
    int wc[MAX_N];

    int tw = 0;  // total weight, not tw
    for (i = 0; i < MAX_N; ++i)
    {
        scanf("%d", &wc[i]);
        tw += wc[i] * wi[i];
    }
    // printf("%d\n", total);

    int dp[MAX_WEIGHT] = {0};
    int w, wii;
    dp[0] = dp[tw] = 1;
    for (i = 0; i < MAX_N; ++i)
    {
        wii = wi[i];
        for (j = 0; j < wc[i]; ++j)
            for (w = tw - 1; w >= wii; --w)
                dp[w] = dp[w - wii];
    }

    int ans = 0;
    for (w = 1; w <= tw; ++w)
        ans += dp[w];
    
    printf("Total=%d", ans);

    return 0;
}