
// P2872 [USACO07DEC]道路建设Building Roads
// https://www.luogu.org/problemnew/show/P2872


#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef double WDT;


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
    int u, v;
    WDT w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;   // min first, max last
    }
};

struct Point
{
    int x, y;
    WDT d(const Point &b) const
    {
        return sqrt((WDT)(x - b.x) * (x - b.x) + (WDT)(y - b.y) * (y - b.y));
    }
};


WDT mst_kruskal(DisjointSet &dset, Edge *edges, int m)
{
    int i, j, k;
    WDT min_cost = 0.0;

    sort(edges, edges + m);
    for (k = 0; k < m; ++k)
    {
        i = edges[k].u;
        j = edges[k].v;
        if (!dset.equivalent(i, j))
        {
            min_cost += edges[k].w;
            dset.unite(i, j);
        }    
    }
    return min_cost;
}

int main()
{
    int n, m, k, i, j;

    scanf("%d %d", &n, &k);

    // vertices id : 1...n
    DisjointSet dset = DisjointSet(n);
    Point *points = (Point *)malloc((n + 1) * sizeof(Point));
    for (i = 1; i <= n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);

    // edges id : 0...(m - 1)
    Edge *edges = (Edge *)malloc((n * n / 2) * sizeof(Edge));

    m = 0;
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= n; ++j)
        {
            edges[m].u = i;
            edges[m].v = j;
            edges[m].w = points[i].d(points[j]);
            ++m;
        }

    while (k--)
    {
        scanf("%d %d", &i, &j);
        dset.unite(i, j);
    }

    WDT min_cost = mst_kruskal(dset, edges, m);
    printf("%.2lf\n", min_cost);
    return 0;
}


