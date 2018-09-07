
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

typedef long long INT64;

const int MAX_N = 100010;
const int MAX_E = 200000 * 2;
const INT64 INF = 0x7ffffffffffff;

int n, m, n_dead, radius, P, Q;

INT64 dist[MAX_N];

int head[MAX_N], n_edges;
bool dead[MAX_N], danger[MAX_N];

struct Edge 
{
    int v, next;
    INT64 w;
};

struct Vertex
{
    int v;
    INT64 spe;
    Vertex(int v, INT64 d) : v(v), spe(d) {}
    bool operator<(const Vertex &b) const
    {
        return spe > b.spe;   // min first, max last
    }
};

Edge edges[MAX_E + 1];

void add_edge(int u, int v, INT64 w = 1L)
{
    edges[++n_edges].v = v;
    edges[n_edges].w = w;
    edges[n_edges].next = head[u];

    head[u] = n_edges;
}


void dijkstra(int src)
{
    queue<Vertex> pq;
    int i, j, k;
    for (i = 1; i <= n; ++i)
        dist[i] = INF;
    
    pq.push(Vertex(src, 0));
    dist[src] = 0;
    while (!pq.empty())
    {
        Vertex v = pq.front();
        pq.pop();
        i = v.v;
        if (v.spe > dist[i]) continue;
        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (dist[j] > dist[i] + edges[k].w)
            {
                dist[j] = dist[i] + edges[k].w;
                pq.push(Vertex(j, dist[j]));
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

int main()
{
    scanf("%d%d%d%d", &n, &m, &n_dead, &radius);
    scanf("%d%d", &P, &Q);

    int i, j, k;
    for (k = 1; k <= n_dead; ++k)
    {
        read_num(i);
        dead[i] = 1;
    }
    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        if (dead[i] && dead[j])
            continue;
        if (dead[i])
            add_edge(0, j), add_edge(j, 0);
        else if (dead[j])
            add_edge(0, i), add_edge(i, 0);
        else
            add_edge(i, j), add_edge(j, i);
    }

    dijkstra(0);
    for (i = 1; i <= n; ++i)
        if (dist[i] <= radius)
            danger[i] = 1;

    for (i = 1; i <= n_edges; ++i)
    {
        if (danger[edges[i].v])
            edges[i].w = Q;
        else if (dead[edges[i].v])
            edges[i].w = INF;
        else
            edges[i].w = P;

        if (edges[i].v == 1 || edges[i].v == n)
            edges[i].w = 0;

    }
    dijkstra(1);
    printf("%lld\n", dist[n]);

    return 0;
}
