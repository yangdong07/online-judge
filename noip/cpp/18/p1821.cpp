
// P1821 [USACO07FEB]银牛派对Silver Cow Party
// https://www.luogu.org/problemnew/show/P1821


#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x7fffffff;
const int MAX_V = 1000;
const int MAX_E = 100000;

struct edge  
{
    int v, w, next;
};

struct Graph
{
    int n_vertices;
    int n_edges;

    int vertices[MAX_V];
    edge edges[MAX_E + 1];

    Graph(int n) : n_vertices(n), n_edges(0)
    {
        memset(vertices, 0, sizeof(vertices));
    }

    void add_edge(int u, int v, int w)
    {
        edges[++n_edges].v = v;
        edges[n_edges].w = w;
        edges[n_edges].next = vertices[u];
        vertices[u] = n_edges;
    }
};

struct vertex 
{
    int v, d;
    vertex(int v, int d) : v(v), d(d) {}
    bool operator<(const vertex &b) const
    {
        return d > b.d;   // min first, max last
    }
};

void dijkstra(Graph &g, int src, int dist[])
{
    int i, j, k, spe;
    for (i = 0; i < g.n_vertices; ++i)
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
        for (k = g.vertices[i]; k; k = g.edges[k].next)
        {
            j = g.edges[k].v;
            if (dist[i] + g.edges[k].w < dist[j])
            {
                dist[j] = dist[i] + g.edges[k].w;
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

int main()
{
    int n, m, src, i, j, k, weight;
    read_num(n);
    read_num(m);
    read_num(src);

    Graph g1 = Graph(n), g2 = Graph(n);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        g1.add_edge(i - 1, j - 1, weight);
        g2.add_edge(j - 1, i - 1, weight);
    }

    int dist1[MAX_V], dist2[MAX_V];
    dijkstra(g1, src - 1, dist1);
    dijkstra(g2, src - 1, dist2);


    int max_d = 0;
    for (i = 0; i < n; ++i)
        max_d = max(dist1[i] + dist2[i], max_d);
    printf("%d\n", max_d);

    return 0;
}