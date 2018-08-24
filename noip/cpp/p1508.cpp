// P1508 Likecloud-吃、吃、吃
// https://www.luogu.org/problemnew/show/P1508

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max(a, max(b, c)); }

int main()
{
    const int MIN_INT = - (1 << 30);
    const int MAX_N = 210;
    int m, n, i, j;
    scanf("%d %d", &m, &n);

    int a[MAX_N][MAX_N];
    for (i = 0; i <= m + 1; ++i)
        a[i][0] = a[i][n + 1] = MIN_INT;
    for (j = 0; j <= n + 1; ++j)
        a[0][j] = a[m + 1][j] = MIN_INT;

    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);

    for (i = 2; i <= m; ++i)
    {
        for (j = 1; j <= n; ++j)
            a[i][j] += max3(a[i - 1][j - 1], a[i - 1][j], a[i - 1][j + 1]);
    }
    
    int mid = (n + 1) / 2;
    printf("%d", max3(a[m][mid - 1], a[m][mid], a[m][mid + 1]));
    
    return 0;
}