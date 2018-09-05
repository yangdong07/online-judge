
// P2299 Mzc和体委的争夺战
// https://www.luogu.org/problemnew/show/P2299

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 2501;
const int INF = 1 << 29;

int adj[MAX_N][MAX_N] = {0};

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

void dijkstra(int src, int dist[], int n)
{
    int i, j, k, min_spe;
    bool visit[MAX_N];
    for (i = 1; i <= n; i++)
        dist[i] = INF, visit[i] = false;
    dist[src] = 0;

    for (k = 0; k < n - 1; ++k)
    {
        // find min shortest path estimate
        min_spe = INF;
        for (j = 1; j <= n; ++j)
            if (!visit[j] && dist[j] <= min_spe)
                min_spe = dist[i], i = j;
        visit[i] = true;
        if (dist[i] == INF) continue;
        for (j = 1; j <= n; ++j)
            if (!visit[j] && adj[i][j] < INF && dist[i] + adj[i][j] < dist[j])
                dist[j] = dist[i] + adj[i][j];
    }
}

int main()
{
    int n, m, i, j, k;
    n = read_num();
    m = read_num();
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            adj[i][j] = INF;
    for (k = 0; k < m; ++k)
    {
        i = read_num(), j = read_num();
        adj[i][j] = adj[j][i] = min(adj[i][j], read_num());
    }
    for (i = 1; i <= n; ++i)
        adj[i][i] = 0;

    int dist[MAX_N];
    dijkstra(1, dist, n);
    // for (i = 1; i <= n; ++i)
    //     printf("%d ", dist[i]);
    // printf("\n");
    printf("%d\n", dist[n]);

    return 0;
}