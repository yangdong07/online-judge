

/*
    Minimum Spanning Tree - Prim algorithm

    Luogu P3366 评测结果 ： 200ms
*/


#include <cstdio>
#include <queue>

using namespace std;

typedef int WDT;            // Weight Data Type

const int MAX_V = 5000;
const int MAX_E = 200000 * 2;
const WDT INF = 1 << 29;

struct Edge 
{
    int v, next;
    WDT w;
    Edge() : v(0), next(0), w(0) {}
    Edge(int v, WDT w) : v(v), next(0), w(w) {}
    bool operator<(const Edge &rhs) const
    {
        return w > rhs.w;   // min first, max last
    }
};

struct Graph
{
    int n_vertices;
    int n_edges;
    int adjs[MAX_V];
    Edge edges[MAX_E + 1];

    // vertices from 0 to n - 1;
    Graph(int n) : n_vertices(n), n_edges(0) {}

    // edges is array-linklist, adjs[i]-> linked index of edges from i;
    void add_edge(int u, int v, WDT w)
    {
        edges[++n_edges].v = v;
        edges[n_edges].w = w;
        edges[n_edges].next = adjs[u];
        adjs[u] = n_edges;
    }
};


// Minimum Spanning Tree start from root, return minimum cost
bool mst_prim(Graph &g, int root, WDT &min_cost)   
{
    min_cost = 0;
    priority_queue<Edge> pq;

    int visit_count = 0, i, j, k;
    bool visit[MAX_V] = {false};
    WDT weight[MAX_V];
    for (i = 0; i < g.n_vertices; ++i)
        weight[i] = INF;

    pq.push(Edge(root, 0));
    weight[root] = 0;

    while (!pq.empty() && visit_count < g.n_vertices)
    {
        Edge e = pq.top();
        pq.pop();
        if (visit[e.v]) continue;
        visit[e.v] = true;
        ++visit_count;
        min_cost += e.w;
        for (k = g.adjs[e.v]; k; k = g.edges[k].next)
        {
            j = g.edges[k].v;
            if (!visit[j] && g.edges[k].w < weight[j])
            {
                weight[j] = g.edges[k].w;
                pq.push(g.edges[k]);
            }
        }
    }

    return visit_count == g.n_vertices;
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
    int n, m, i, j, k, weight;
    scanf("%d %d", &n, &m);

    Graph g = Graph(n);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        g.add_edge(i - 1, j - 1, (WDT)weight);
        g.add_edge(j - 1, i - 1, (WDT)weight);
    }
    WDT min_cost;
    if (mst_prim(g, 0, min_cost))
        printf("%d\n", min_cost);
    else
        printf("orz\n");

    return 0;
}