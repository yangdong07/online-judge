
// P2213 [USACO14MAR]懒惰的牛The Lazy Cow_Sliver
// https://www.luogu.org/problemnew/show/P2213

#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    const int MAX_N = 401;
    int a[MAX_N][MAX_N], b[MAX_N * 2][MAX_N * 2] = {0};
    int n, m, k, i, j;
    scanf("%d%d", &n, &k);
    m = 2 * n - 1;

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            b[i + j - 1][n - i + j] = a[i][j];

    // for (i = 1; i <= m; ++i)
    // {
    //     for (j = 1; j <= m; ++j)
    //         printf("%-4d ", b[i][j]);
    //     printf("\n");
    // }

    for (i = 1; i <= m; ++i)
        for (j = 1; j <= m; ++j)
            b[i][j] += (b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]);
    int x, y, x1, x2, y1, y2;
    int result = 0;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
        {
            x = i + j - 1, y = n - i + j;
            x1 = max(1, x - k);
            x2 = min(m, x + k);
            y1 = max(1, y - k);
            y2 = min(m, y + k);

            result = max(result, b[x2][y2] - b[x1 - 1][y2] - b[x2][y1 - 1] + b[x1 - 1][y1 - 1]);
        }
    printf("%d", result);
    return 0;
}