
// P1119 灾后重建
// https://www.luogu.org/problemnew/show/P1119

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }

void read_num(int &num)
{
    char c;
    num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}

int main()
{
    const int MAX_N = 200;
    const int INF = 0x3fffffff;
    int n, m, i, j, k;
    int t[MAX_N], dist[MAX_N][MAX_N];

    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
        scanf("%d", &t[i]);

    for (i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
        for (j = i + 1; j < n; ++j)
            dist[j][i] = dist[i][j] = INF;
    }
    
    int w;
    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(w);
        dist[i][j] = dist[j][i] = w;
    }
    // for (i = 0; i < n; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //         printf("%-3d", dist[i][j] == INF ? -1 : dist[i][j]);
    //     printf("\n");
    // }
    int q, qi, qj, qt;
    scanf("%d", &q);

    k = 0;
    while (q--)
    {
        read_num(qi);
        read_num(qj);
        read_num(qt);
        // scanf("%d %d %d", &qi, &qj, &qt);
        // Floyd-Warshall
        for (; k < n && t[k] <= qt; ++k)
        {
            // printf("%d %d %d\n", k, t[k], qt);
            // 
            // for (i = 0; i < k; ++i)
            //     for (j = 0; j < k; ++j)
            //         dist[i][k] = dist[k][i] = min(dist[i][k], dist[i][j] + dist[j][k]);
            // for (i = 0; i < k; ++i)
            //     for (j = 0; j < k; ++j)
            //         dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            for (i = 0; i < n; ++i)
                for (j = 0; j < n; ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

            // for (i = 0; i < n; ++i)
            // {
            //     for (j = 0; j < n; ++j)
            //         printf("%-3d", dist[i][j] == INF ? -1 : dist[i][j]);
            //     printf("\n");
            // }
        }

        if (qi >= k || qj >= k || dist[qi][qj] == INF)
            printf("-1\n");
        else
            printf("%d\n", dist[qi][qj]);
    }

    return 0;
}