// P1855 榨取kkksc03
// https://www.luogu.org/problemnew/show/P1855

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_M = 201;
    const int MAX_T = 201;
    int n, M, T;

    scanf("%d %d %d", &n, &M, &T);

    int mi, ti, m, t;
    int dp[MAX_M][MAX_T] = {0};

    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &mi, &ti);
        for (m = M; m >= mi; --m)
            for (t = T; t >= ti; --t)
                dp[m][t] = max(dp[m][t], dp[m - mi][t - ti] + 1);
    }

    printf("%d", dp[M][T]);

    return 0;
}