// P1060 开心的金明
// https://www.luogu.org/problemnew/show/P1060


#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 30000;
    const int MAX_M = 27;

    int n, m, i, j;
    scanf("%d %d", &n, &m);

    int v[MAX_M], w[MAX_M], dp[MAX_N];
    // maximize  sum(vw), subject to  sum(v) < n;

    for (j = 1; j <= m; ++j)
        scanf("%d %d", &v[j], &w[j]);

    for (i = 0; i <= n; ++i)
        dp[i] = 0;

    for (j = 1; j <= m; ++j)
        for (i = n; i > 0; --i)
            if (i >= v[j])
                dp[i] = max(dp[i], dp[i - v[j]] + v[j] * w[j]);
    
    printf("%d", dp[n]);

    return 0;
}