// P1282 多米诺骨牌
// https://www.luogu.org/problemnew/show/P1282

#include <cstdio>
#include <algorithm>

using namespace std;

bool greater(int a, int b) { return a > b; }

int main()
{   
    const int MAX_N = 1001;
    const int RANGE = 50;
    const int MAX_INT = 1 << 30;

    int n, i, j;
    int w[MAX_N];

    scanf("%d", &n);
    int t1, t2;
    int target = 0;
    for (i = 0, j = 0; i < n; ++i)
    {
        scanf("%d %d", &t1, &t2);
        if (t1 != t2)
            w[j++] = (t1 - t2) * 2;
        target += (t1 - t2);
    }
    n = j;
    if (target < 0)
    {
        target = -target;
        for (i = 0; i < n; ++i)
            w[i] = -w[i];
    }
    sort(w, w + n, greater);

    // printf("%d\n", target);
    // for (i = 0; i < n; ++i)
    //     printf("%3d ", w[i]);
    // printf("\n");

    int dp[RANGE * 3];
    for (i = 0; i < RANGE * 3; ++i)
        dp[i] = MAX_INT;

    // greedy jump into  [target - RANGE, target + RANGE];
    int step = 0;
    for (i = 0; i < n && target >= RANGE && w[i] > 0; ++i, ++step)
        target -= w[i];
    dp[0] = step;

    for (; i < n && w[i] > 0; ++i)
    {
        for (j = target + RANGE; j >= w[i]; --j)
            dp[j] = min(dp[j], dp[j - w[i]] + 1);
    }

    for (; i < n; ++i)
    {
        for (j = 0; j <= target + RANGE - w[i]; ++j)
            dp[j] = min(dp[j], dp[j - w[i]] + 1);
    }

    // for (j = target - RANGE; j < target + RANGE; ++j)
    //     printf("%3d ", j);
    // printf("\n");
    // for (j = 0; j < RANGE * 2; ++j)
    //     printf("%3d ", dp[j] == MAX_INT ? -1 : dp[j]);
    // printf("\n");

    for (i = 0; i < RANGE; ++i)
    {
        if (dp[target + i] != MAX_INT || dp[target - i] != MAX_INT)
        {
            printf("%d", min(dp[target + i], dp[target - i]));
            return 0;
        }
    }
    // printf("%d", dp[target]);

    return 0;
}