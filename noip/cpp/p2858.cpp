// P2858 [USACO06FEB]奶牛零食Treats for the Cows
// https://www.luogu.org/problemnew/show/P2858

#include <cstdio>
#include <algorithm>

#define MAX_N 2001

int main()
{
    int n, i, j;
    scanf("%d", &n);

    int v[MAX_N];

    for (i = 0; i < n; ++i)
        scanf("%d", &v[i]);

    // for (i = 0; i < n; ++i)
    //     printf("%3d ", v[i]);
    // printf("\n");

    int dp[MAX_N] = {0};
    for (int k = 0; k < n; ++k)
    {
        for (i = 0; i < n - k; ++i)
            dp[i] = std::max(dp[i] + v[i + k] * (n - k), dp[i + 1] + v[i] * (n - k));
        // for (i = 0; i < n - k; ++i)
        //     printf("%3d ", dp[i]);
        // printf("\n");
    }
    
    printf("%d", dp[0]);

    return 0;
}