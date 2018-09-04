
// P1529 回家 Bessie Come Home
// https://www.luogu.org/problemnew/show/P1529

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 26 * 2;
const int INF = 60000;  // MAX_N * (1000)

int adj[MAX_N][MAX_N];

int c2i(char c)
{
    if ('a' <= c && c <= 'z')
        return c - 'a';
    else
        return c - 'A' + 26;
}

int min_distance_index(int dist[], bool visit[], int n)
{
    int min_d = INF, min_i;
    for (int i = 0; i < n; ++i)
        if (!visit[i] && dist[i] <= min_d)
            min_d = dist[i], min_i = i;
    return min_i;
}

void dijkstra(int src, int dist[], int n)
{
    int i, j, k;
    bool visit[MAX_N];
    for (i = 0; i < n; i++)
        dist[i] = INF, visit[i] = false;
    dist[src] = 0;

    for (k = 0; k < n - 1; ++k)
    {
        i = min_distance_index(dist, visit, n);
        visit[i] = true;
        if (dist[i] == INF) continue;
        for (j = 0; j < n; ++j)
            if (!visit[j] && adj[i][j] != INF && dist[i] + adj[i][j] < dist[j])
                dist[j] = dist[i] + adj[i][j];
    }
}

int main()
{
    int i, j, k;
    for (i = 0; i < MAX_N; ++i)
        for (j = 0; j < MAX_N; ++j)
            adj[i][j] = INF;

    int p, d;
    char a, b;

    scanf("%d\n", &p);
    for (k = 0; k < p; ++k)
    {
        scanf("%c %c %d\n", &a, &b, &d);
        i = c2i(a), j = c2i(b);
        adj[i][j] = adj[j][i] = min(adj[i][j], d);
    }

    int dist[MAX_N];
    dijkstra(c2i('Z'), dist, MAX_N);

    int min_i, min_dist = INF;
    for (i = 'A'; i < 'Z'; ++i)
        if (dist[c2i(i)] < min_dist)
            min_dist = dist[c2i(i)], min_i = i;
    
    // for (i = 0; i < MAX_N; ++i)
    //     printf("%c %d\n", i2c(i), dist[i]);
    
    printf("%c %d\n", min_i, min_dist);
}