
// P2951 [USACO09OPEN]捉迷藏Hide and Seek
// https://www.luogu.org/problemnew/show/P2951

#include <cstdio>
#include <queue>

using namespace std;

const int INF = 0x7fffffff;
const int MAX_V = 20000;
const int MAX_E = 100000;

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
    int n, m, i, j, k;
    read_num(n);
    read_num(m);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        add_edge(i - 1, j - 1, 1);
        add_edge(j - 1, i - 1, 1);
    }

    int dist[MAX_V];
    dijkstra(0, dist, n);

    int max_i = 0, max_d = 0, total;
    for (i = 0; i < n; ++i)
    {
        // printf("%d ", dist[i]);
        if (max_d < dist[i])
        {
            max_d = dist[i];
            max_i = i;
            total = 1;
        }
        else if (max_d == dist[i])
            ++total;
    }
    printf("%d %d %d\n", max_i + 1, max_d, total);

    return 0;
}