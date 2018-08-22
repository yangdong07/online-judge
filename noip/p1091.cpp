// P1091 合唱队形
// https://www.luogu.org/problemnew/show/P1091

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 101;
    int n;
    scanf("%d", &n);

    int height[MAX_N], i, j;
    int dp1[MAX_N], dp2[MAX_N], max_dp = 0;

    for (i = 0; i < n; ++i)
        scanf("%d", &height[i]);
    
    // from left to right
    for (i = 0; i < n; ++i)
    {
        dp1[i] = 1;
        for (j = 0; j < i; ++j)
            if (height[i] > height[j])
                dp1[i] = max(dp1[i], dp1[j] + 1);
    }
    // from right to left
    for (i = n - 1; i >= 0; --i)
    {
        dp2[i] = 1;
        for (j = i + 1; j < n; ++j)
            if (height[i] > height[j])
                dp2[i] = max(dp2[i], dp2[j] + 1);
        max_dp = max(max_dp, dp1[i] + dp2[i] - 1);
    }

    // for (int i = 0; i < n; ++i)
    //     printf("%4d ", height[i]);
    // printf("\n");
    // for (int i = 0; i < n; ++i)
    //     printf("%4d ", dp1[i]);
    // printf("\n");
    // for (int i = 0; i < n; ++i)
    //     printf("%4d ", dp2[i]);
    // printf("\n");

    printf("%d", n - max_dp);

    return 0;
}