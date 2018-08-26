// P2722 总分 Score Inflation
// https://www.luogu.org/problemnew/show/P2722

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_T = 10001;
    int T, n;
    scanf("%d %d", &T, &n);

    int ti, si, t;
    int dp[MAX_T] = {0};
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &si, &ti);
        for (t = ti; t <= T; ++t)
            dp[t] = max(dp[t], dp[t - ti] + si);
    }
    printf("%d", dp[T]);
    return 0;
}