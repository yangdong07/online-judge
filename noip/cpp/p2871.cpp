// P2871 [USACO07DEC]手链Charm Bracelet
// https://www.luogu.org/problemnew/show/P2871

#include <cstdio>

#define MAX_N 3403
#define MAX_W 12881

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int dp[MAX_W] = {0};
    int v, w;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &w, &v);
        for (int j = m; j >= w; --j)
            dp[j] = max(dp[j], dp[j - w] + v);
    }

    printf("%d", dp[m]);

    return 0;
}