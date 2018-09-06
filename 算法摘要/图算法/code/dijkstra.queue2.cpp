
/*
    dijkstra algorithm
    no vector
    1. graph: edges, use array list
    2. vertices: shortest path estimate
    3. use priority queue

    please use luogu p4779 test examples
    比实现二叉堆的性能略差一些，但是贵在写起来方便。这应该是综合考虑最优的版本。
    806ms，O2优化： 188ms
*/


#include <cstdio>
#include <queue>

using namespace std;

struct edge // 实际上是一个用数组实现的单向链表
{
    int v, w, next;
};

struct vertex  // 实际上是每个点的最短路径估计，需要加入到 优先级队列中。
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
        if (spe != dist[i]) continue;
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