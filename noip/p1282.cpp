// P1282 多米诺骨牌
// https://www.luogu.org/problemnew/show/P1282

#include <cstdio>

int abs(int a) { return a < 0 ? -a : a; };

int count[11] = {0}; // count for -10 -8 -6 -4 -2 0 2 4 6 8 10
int min_flip = 0;
int min_s = 1 << 30;

bool dfs(int target, int flip)
{
    if (abs(min_s) < abs(target))
    {
        min_s = target;
        min_flip = flip;
    }

    bool flag = false;
    for (int i = 0; i < 11; ++i)
    {
        if (count[i])
        {
            count[i]--;
            
        }
    }
}

int main()
{   
    const int MAX_N = 1001;
    int n, i, j;
    int a[MAX_N];

    scanf("%d", &n);
    int t1, t2;
    int target = 0;
    for (i = 0, j = 0; i < n; ++i)
    {
        scanf("%d %d", &t1, &t2);
        if (t1 != t2)
            a[j++] = -(t1 - t2) * 2;
        count[t1 - t2 + 5]++;
        target += (t1 - t2);
    }
    count[5] = 0;  // remove 0;
    n = j;
    if (target == 0)

    for (i = 0; i <= 10; ++i)
        printf("%d ", count[i]);
    printf("\n");
    for (i = 0; i < j; ++i)
        printf("%d ", a[i]);
    printf("\n");
    printf("%d ", target);

    // int a[MAX_N], j = 0, t;
    // for (i = 5; i >= 1; --i)
    //     if (count[i] >= 0)
    //         for (t = count[i]; t; --t)
    //             a[j++] = - i * 2;
    //     else
    //         for (t = count[i]; t; ++t)
    //             a[j++] = i * 2;
    // n = j;
    
    // for (i = 0; i < n; ++i)
    //     printf("%d ", a[i]);

    n = j;
    int dp[MAX_N][MAX_N];
    // for (i = 0; i < n; ++i)
    //     dp[i] = abs(a[i] - a[i])

    // int x, y, min_s = target, min_i = 0;
    // // printf("\n");
    // for (i = 0; i <= n; ++i)
    //     dp[i][0] = target;
    // for (i = 1; i <= n; ++i)
    // {
    //     dp[i][i] = dp[i - 1][i - 1] + a[i - 1];
    //     for (j = i + 1; j <= n; ++j)
    //     {
    //         x = dp[j - 1][i - 1] + a[j - 1];
    //         y = dp[j - 1][i];
    //         dp[j][i] = abs(x) <= abs(y) ? x : y;
    //     }
    //     if (abs(dp[n][i]) < abs(min_s))
    //     {
    //         min_s = dp[n][i];
    //         min_i = i;
    //     }
    //     for (j = i; j <= n; ++j)
    //         printf("%3d ", dp[j][i]);
    //     printf("\n");
    // }
    // printf("%d", min_i);
    return 0;
}