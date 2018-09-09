
// P1340 兽径管理
// https://www.luogu.org/problemnew/show/P1340


#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;


struct DisjointSet
{
    int n;
    int *s;
    DisjointSet(int n) : n(n)
    {
        s = (int *)malloc((n + 1) * sizeof(int));
        reset();
    }
    void reset()
    {
        for (int i = 0; i <= n; ++i)
            s[i] = i;
    }
    int find(int x)
    {
        if (s[x] == x)
            return x;
        return s[x] = find(s[x]);
    }
    void unite(int x, int y)
    {
        s[find(x)] = find(y);
    }
    bool equivalent(int x, int y)
    {
        return find(x) == find(y);
    }
};

struct Edge
{
    int id, u, v, w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;
    }
};

const int MAX_E = 6000 + 1;
bool in_mst[MAX_E];
bool removed[MAX_E] = {false};

int mst_kruskal(DisjointSet &dset, Edge *edges, int m)
{
    dset.reset();
    memset(in_mst, false, sizeof(in_mst));
    int min_cost = 0, i, j, k;

    for (k = 1; k <= m; ++k)
    {
        if (removed[edges[k].id]) continue;
        i = edges[k].u;
        j = edges[k].v;
        if (!dset.equivalent(i, j))
        {
            min_cost += edges[k].w;
            dset.unite(i, j);
            in_mst[edges[k].id] = true;
        }
    }
    return min_cost;
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

    scanf("%d %d", &n, &m);

    // vertices id : 1...n
    // edges id : 1...m
    Edge *edges = (Edge *)malloc((m + 1) * sizeof(Edge));
    
    for (k = 1; k <= m; ++k)
    {
        read_num(edges[k].u);
        read_num(edges[k].v);
        read_num(edges[k].w);
        edges[k].id = k;
    }

    // try connect

    DisjointSet dset = DisjointSet(n);
    int connected = 1, k_connected;
    for (k_connected = 1; k_connected <= m; ++k_connected)
    {
        i = edges[k_connected].u;
        j = edges[k_connected].v;
        if (!dset.equivalent(i, j))
        {
            dset.unite(i, j);
            if (++connected == n) break;
        }
        printf("-1\n");
    }

    int result[MAX_E];
    sort(edges + 1, edges + m + 1);
    int min_cost = mst_kruskal(dset, edges, m);
    result[m] = min_cost;
    for (k = m - 1; k >= k_connected; --k)
    {
        removed[k + 1] = true;
        if (in_mst[k + 1])
            min_cost = mst_kruskal(dset, edges, m);
        result[k] = min_cost;
    }
    for (k = k_connected; k <= m; ++k)
        printf("%d\n", result[k]);

    return 0;
}

