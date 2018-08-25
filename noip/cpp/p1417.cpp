// P1417 烹调方案
// https://www.luogu.org/problemnew/show/P1417

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long INT64;
const int MAX_N = 51;
const int MAX_T = 100001;

INT64 a[MAX_N];
INT64 b[MAX_N];
INT64 c[MAX_N];

int cmp_cb(int i, int j)
{
    return c[i] * b[j] < c[j] * b[i];
}


int main()
{
    int T, n, t, i, j;
    scanf("%d %d", &T, &n);
    for (i = 0; i < n; ++i)
        scanf("%lld", &a[i]);
    for (i = 0; i < n; ++i)
        scanf("%lld", &b[i]);
    for (i = 0; i < n; ++i)
        scanf("%lld", &c[i]);
    
    int idx[MAX_N];
    for (i = 0; i < n; ++i)
        idx[i] = i;
    sort(idx, idx + n, cmp_cb);
    
    INT64 dp[MAX_T] = { 0 };

    for (i = 0; i < n; ++i)
    {
        j = idx[i];
        for (t = T; t >= c[j]; --t)
            dp[t] = max(dp[t], dp[t - c[j]] + a[j] - t * b[j]);
        // for (t = 0; t <= T; ++t)
        //     printf("%4lld", dp[t]);
        // printf("\n");
    }

    INT64 max_s = 0;
    for (t = 0; t <= T; ++t)
        max_s = max(max_s, dp[t]);

    printf("%lld", max_s);

    return 0;
}