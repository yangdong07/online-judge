// P3717 [AHOI2017初中组]cover
// https://www.luogu.org/problemnew/show/P3717

#include <cstdio>

#define MAX_N 101
#define MAX_M 101

int main()
{
    int n, m, r;
    int i, j, k;
    int grid[MAX_N][MAX_N] = { 0 };
    int x, y; // radar pos;
    int detect[MAX_N][MAX_N];
    scanf("%d %d %d", &n, &m, &r);

    // draw radar detect area
    for (i = 0; i <= 2 * r; ++i)
        for (j = 0; j <= 2 * r; ++j)
            detect[i][j] = (i - r) * (i - r) + (j - r) * (j - r) <= r * r;

    for (k = 0; k < m; ++k)
    {
        scanf("%d %d", &x, &y);
        for (i = x - r; i <= x + r; ++i)
            for (j = y - r; j <= y + r; ++j)
                if (i > 0 && i <= n && j > 0 && j <= n)
                    grid[i][j] |= detect[i - x + r][j - y + r];
    }

    int count = 0;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            count += grid[i][j];

    // for (i = 1; i <= n; ++i)
    // {
    //     for (j = 1; j <= n; ++j)
    //         printf(grid[i][j] ? "*" : " ");
    //     printf("\n");
    // }
    printf("%d", count);
}