
// P2888 [USACO07NOV]牛栏Cow Hurdles
// https://www.luogu.org/problemnew/show/P2888

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int main()
{
    const int INF = 1 << 30;
    const int MAX_N = 301;
    int n, m, t, i, j, k;
    scanf("%d %d %d", &n, &m, &t);

    int height[MAX_N][MAX_N];  // min (max height) from i to j;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            height[i][j] = INF;

    for (k = 0; k < m; ++k)
    {
        i = read_num(), j = read_num();
        height[i][j] = read_num();
    }

    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                height[i][j] = min(height[i][j], max(height[i][k], height[k][j]));
    
    for (k = 0; k < t; ++k)
    {
        scanf("%d %d", &i, &j);
        printf("%d\n", height[i][j] < INF ? height[i][j] : -1);
    }

    return 0;
}