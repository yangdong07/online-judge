
// P1195 口袋的天空
// https://www.luogu.org/problemnew/show/P1195

#include <cstdio>
#include <algorithm>

using namespace std;

struct DisjointSet
{
    int n;
    int *s;
    DisjointSet(int n) : n(n)
    {
        s = (int *)malloc((n + 1) * sizeof(int));
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
    int u, v, w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;   // min first, max last
    }
};


int limit, reduce = 0;

int mst_kruskal(DisjointSet &dset, Edge *edges, int m)
{
    int i, j, k;
    int min_cost = 0;

    sort(edges, edges + m);
    for (k = 0; k < m; ++k)
    {
        i = edges[k].u;
        j = edges[k].v;
        if (!dset.equivalent(i, j))
        {
            min_cost += edges[k].w;
            dset.unite(i, j);
            ++reduce;
            if (reduce == dset.n - limit)
                return min_cost;
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
    int n, m, i;

    scanf("%d %d %d", &n, &m, &limit);
    // vertices id : 1...n
    DisjointSet dset = DisjointSet(n);
    // edges id : 0...(m - 1)
    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    for (i = 0; i < m; ++i)
    {
        read_num(edges[i].u);
        read_num(edges[i].v);
        read_num(edges[i].w);
    }

    int min_cost = mst_kruskal(dset, edges, m);
    if (n - reduce == limit)
        printf("%d\n", min_cost);
    else
        printf("No Answer\n");
    return 0;
}
