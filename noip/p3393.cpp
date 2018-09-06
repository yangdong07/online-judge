
// P3393 逃离僵尸岛
// https://www.luogu.org/problemnew/show/P3393

#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long INT64;

const INT64 INF = 0x3ffffffffffffff;
const int MAX_V = 100000;
const int MAX_E = 200000 * 2;

struct edge 
{
    int v, next;
    INT64 w;
};

struct vertex 
{
    int v;
    INT64 d;
    vertex(int v, INT64 d) : v(v), d(d) {}
    bool operator<(const vertex &b) const
    {
        return d > b.d;   // min first, max last
    }
};

edge edges[MAX_E + 1];
int head[MAX_V] = {0}, ec = 0;

void add_edge(int u, int v, INT64 w)
{
    edges[++ec].v = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec;
}

void dijkstra(int src, INT64 dist[], int n)
{
    int i, j, k;
    INT64 spe;
    for (i = 0; i < n; ++i)
        dist[i] = INF;
    priority_queue<vertex> pq;

    dist[src] = 0;
    pq.push(vertex(src, 0));

    while (!pq.empty())
    {
        i = pq.top().v;
        spe = pq.top().d;
        pq.pop();
        if (spe > dist[i]) continue;
        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (dist[i] + edges[k].w < dist[j])
            {
                dist[j] = dist[i] + edges[k].w;
                pq.push(vertex(j, dist[j]));
            }
        }
    }
}

void read_num(int &num)
{
    char c;
    num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}


void bfs(int start, int visit[], int depth)
{
    int i, j, k;
    queue<int> vq;
    visit[start] = 1;
    vq.push(start);

    while (!vq.empty())
    {
        i = vq.front();
        vq.pop();
        if (visit[i] == depth + 1) continue;
        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (!visit[j])
            {
                visit[j] = visit[i] + 1;
                vq.push(j);
            }
        }
    }
}


int main()
{
    int n, m, i, j, k, p, q;
    int n_dead, radius;

    scanf("%d %d %d %d\n", &n, &m, &n_dead, &radius);
    scanf("%d %d\n", &p, &q);

    bool dead[MAX_V] = {false};
    for (k = 0; k < n_dead; ++k)
    {
        scanf("%d", &i);
        dead[i - 1] = true;
    }
    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        add_edge(i - 1, j - 1, 0);
        add_edge(j - 1, i - 1, 0);
    }

    // mark danger city
    int visit[MAX_V] = {0};
    for (i = 0; i < n; ++i)
        if (dead[i])
            bfs(i, visit, radius);
    
    // for (i = 0; i < n; ++i)
    //     printf("%d ", visit[i]);
    // printf("\n");

    // re assign weights
    for (i = 0; i < n; ++i)
    {
        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (visit[j] == 0)
                edges[k].w = p;
            else if (visit[j] == 1)
                edges[k].w = INF;
            else
                edges[k].w = q;
            if (j == 0 || j == n - 1)
                edges[k].w = 0;
        }
    }

    INT64 dist[MAX_V];
    dijkstra(0, dist, n);

    printf("%lld\n", dist[n - 1]);
    // for (i = 0; i < n; ++i)
    //     printf("%lld ", dist[i]);
    // printf("%d", dist[dst - 1]);

    return 0;
}