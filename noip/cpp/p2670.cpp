// P2670 扫雷游戏
// https://www.luogu.org/problemnew/show/P2670

#include <cstdio>

#define MAX_N  102


int main()
{
    int n, m, i, j;
    char M[MAX_N][MAX_N];

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%s", &M[i][1]);

    for (i = 1; i <= n; ++i)
        for (j = 1;  j <= m; ++j)
            if (M[i][j] != '*')
                M[i][j] = 0 + ('*' == M[i-1][j-1])
                    + ('*' == M[i-1][j])
                    + ('*' == M[i-1][j+1])
                    + ('*' == M[i][j-1])
                    + ('*' == M[i][j+1])
                    + ('*' == M[i+1][j-1])
                    + ('*' == M[i+1][j])
                    + ('*' == M[i+1][j+1]) + '0';

    for (i = 1; i <= n; ++i)
    {
        for (j = 1;  j <= m; ++j)
            putchar(M[i][j]);
        putchar('\n');
    }
}