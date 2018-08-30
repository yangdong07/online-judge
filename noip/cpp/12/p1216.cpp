// P1216 [USACO1.5]数字三角形 Number Triangles
// https://www.luogu.org/problemnew/show/P1216


#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 1001;
    int a[MAX_N], dp[MAX_N];
    int n, i, j;

    scanf("%d", &n);

    scanf("%d", &a[1]);  // first line
    dp[1] = a[1];
    for (i = 2; i <= n; ++i)
    {
        for (j = 1; j <= i; ++j)
            scanf("%d", &a[j]);
        
        dp[i] = dp[i - 1] + a[i];
        for (j = i - 1; j > 1; --j)
            dp[j] = max(dp[j], dp[j - 1]) + a[j];
        dp[1] = dp[1] + a[1];

        // for (j = 1; j <= i; ++j)
        //     printf("%d:%d ", a[j], dp[j]);
        // printf("\n");
    }

    int max_sum = 0;
    for (i = 1; i <= n; ++i)
        max_sum = max(max_sum, dp[i]);

    printf("%d", max_sum);

}
