
// P4779 【模板】单源最短路径（标准版）
// https://www.luogu.org/problemnew/show/P4779

#include <cstdio>
#include <queue>

using namespace std;

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

const int INF = 0x7fffffff;
const int MAX_V = 100000;
const int MAX_E = 200000;

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
    int i, j, k;
    bool visit[MAX_V];
    for (i = 0; i < n; ++i)
        dist[i] = INF, visit[i] = false;
    priority_queue<vertex> pq;

    dist[src] = 0;
    pq.push(vertex(src, 0));

    while (!pq.empty())
    {
        i = pq.top().v;
        pq.pop();

        if (visit[i]) continue;
        visit[i] = true;
        // if (spe > dist[i]) continue;
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
    int n, m, src, i, j, k, weight;
    read_num(n);
    read_num(m);
    read_num(src);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        add_edge(i - 1, j - 1, weight);
    }

    int dist[MAX_V];
    dijkstra(src - 1, dist, n);

    for (i = 0; i < n; ++i)
        printf("%d ", dist[i]);

    return 0;
}