// P1115 最大子段和
// https://www.luogu.org/problemnew/show/P1115


#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 200001;
    const int MIN_INT = - (1 << 30);
    int a[MAX_N], dp[MAX_N];
    int n, i;
    scanf("%d", &n);

    dp[0] = 0;
    int max_sum = MIN_INT;
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        dp[i] = (dp[i - 1] < 0) ? a[i] : dp[i - 1] + a[i];
        max_sum = max(max_sum, dp[i]);
    }
    printf("%d", max_sum);
    return 0;
}