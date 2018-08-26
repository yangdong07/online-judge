// P2430 严酷的训练
// https://www.luogu.org/problemnew/show/P2430

#include <cstdio>

#define MAX_N 5001
#define MAX_W 5001

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    int tmp, factor;
    scanf("%d %d", &tmp, &factor);

    factor /= tmp;
    int n, m, i, j;
    scanf("%d %d", &m, &n);

    int iw[MAX_N], w[MAX_N], v[MAX_N];
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &iw[i]);
        iw[i] *= factor;
    }
    
    // for (i = 1; i <= n; ++i)
    //     printf("%d ", iw[i]);
    // printf("\n");

    for (i = 0; i < m; ++i)
    {
        scanf("%d %d", &tmp, &v[i]);
        w[i] = iw[tmp];
        // printf("%d %d\n", w[i], v[i]);
    }

    int W;
    int dp[MAX_W] = {0};
    scanf("%d", &W);
    for (i = 0; i < m; ++i)
        for (j = W; j >= w[i]; --j)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);

    printf("%d", dp[W]);

    return 0;
}