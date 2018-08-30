// P1880 [NOI1995]石子合并
// https://www.luogu.org/problemnew/show/P1880

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 101;
    const int MAX_INT = 1 << 30;

    int a[MAX_N * 2], acc[MAX_N * 2];
    int mindp[MAX_N * 2][MAX_N] = {0};
    int maxdp[MAX_N * 2][MAX_N] = {0};

    int n, t, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &t);
        a[i] = a[i + n] = t;
    }

    acc[0] = 0;
    for (i = 1; i <= n * 2; ++i)
        acc[i] = acc[i - 1] + a[i - 1];

    int l, k, cut, min_s, max_s;
    for (k = 1; k < n; ++k)   // k: len of [l, r], r = l + k
    {
        for (l = 0; l < n * 2 - k; ++l)  // l: left side
        {
            min_s = MAX_INT;
            max_s = 0;
            for (cut = 0; cut < k; ++cut)   // cut: cut size
            {
                min_s = min(min_s, mindp[l][cut] + mindp[l + cut + 1][k - cut - 1]);
                max_s = max(max_s, maxdp[l][cut] + maxdp[l + cut + 1][k - cut - 1]);
            }
            mindp[l][k] = min_s + acc[l + k + 1] - acc[l];
            maxdp[l][k] = max_s + acc[l + k + 1] - acc[l];
        }
    }

    // for (i = 0; i < n * 2; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //         printf("%5d ", mindp[i][j]);
    //     printf("\n");
    // }
    min_s = MAX_INT;
    max_s = 0;
    for (i = 0; i < n; ++i)
    {
        min_s = min(min_s, mindp[i][n - 1]);
        max_s = max(max_s, maxdp[i][n - 1]);
    }

    printf("%d\n%d", min_s, max_s);

    return 0;
}