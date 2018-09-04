
// P2910 [USACO08OPEN]寻宝之路Clear And Present Danger
// https://www.luogu.org/problemnew/show/P2910

#include <cstdio>

const int INF = 1 << 30;

int main()
{
    const int MAX_N = 100;
    const int MAX_M = 10000;
    int n, m, i, j, k;
    scanf("%d %d", &n, &m);
    
    int a[MAX_M];
    for (i = 0; i < m; ++i)
        scanf("%d", &a[i]);

    int dist[MAX_N][MAX_N];
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &dist[i][j]);
    
    // floyd-warshall
    for (k = 0; k < n; ++k)
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    int total = dist[0][a[0] - 1];
    for (i = 1; i < m; ++i)
        total += (dist[a[i - 1] - 1][a[i] - 1]);
    
    printf("%d\n", total);
}