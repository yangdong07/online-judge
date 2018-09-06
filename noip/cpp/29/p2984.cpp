
// P2984 [USACO10FEB]给巧克力Chocolate Giving
// https://www.luogu.org/problemnew/show/P2984

#include <cstdio>
#include <queue>

using namespace std;

const int INF = 0x7fffffff;
const int MAX_V = 50000;
const int MAX_E = 100000 * 2;

struct edge 
{
    int v, w, next;
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

edge edges[MAX_E + 1];
int head[MAX_V] = {0}, ec = 0;

void add_edge(int u, int v, int w)
{
    edges[++ec].v = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec;
}

void dijkstra(int src, int dist[], int n)
{
    int i, j, k, spe;
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

int main()
{
    int n, m, b, i, j, k, weight;
    read_num(n);
    read_num(m);
    read_num(b);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        add_edge(i - 1, j - 1, weight);
        add_edge(j - 1, i - 1, weight);
    }

    int dist[MAX_V];
    dijkstra(0, dist, n);

    for (k = 0; k < b; ++k)
    {
        read_num(i);
        read_num(j);
        printf("%d\n", dist[i - 1] + dist[j - 1]);
    }
    return 0;
}