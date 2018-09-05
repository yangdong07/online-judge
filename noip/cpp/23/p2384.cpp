
// P2384 最短路
// https://www.luogu.org/problemnew/show/P2384

#include <cstdio>
#include <cmath>

const int MOD = 9987;
const int MAX_N = 1000 + 1;
const int INF = 1 << 30;
int adj[MAX_N][MAX_N];

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

void dijkstra(int src, double dist[], int pre[], int n)
{
    int i, j, k;
    double min_spe;
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
            if (!visit[j] && adj[i][j] < INF && dist[i] + log(adj[i][j]) < dist[j])
            {
                dist[j] = dist[i] + log(adj[i][j]);
                pre[j] = i;
            }
    }
}


int main()
{
    int n, m, i, j, k;
    n = read_num();
    m = read_num();

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= n; ++j)
            adj[i][j] = INF;
        adj[i][i] = 0;
    }

    for (k = 0; k < m; ++k)
    {
        i = read_num(), j = read_num();
        adj[i][j] = read_num();
    }

    double dist[MAX_N];
    int pre[MAX_N] = {0};
    dijkstra(1, dist, pre, n);

    // for (i = 1; i <= n; ++i)
    // {
    //     printf("%d -> %d: ", pre[i], i);
    //     printf("%lf\n", exp(dist[i]));
    // }
    // printf("\n");

    int anwser = 1;
    for (i = n; i != 1; i = pre[i])
        anwser = (anwser * adj[pre[i]][i]) % MOD;

    printf("%d\n", anwser);

    return 0;
}