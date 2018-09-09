
// P1991 无线通讯网
// https://www.luogu.org/problemnew/show/P1991

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


int m_forest;

WDT mst_kruskal(DisjointSet &dset, Edge *edges, int m)
{
    int i, j, k, n_forest = dset.n;
    WDT max_edge = 0.0;

    sort(edges, edges + m);
    for (k = 0; k < m; ++k)
    {
        i = edges[k].u;
        j = edges[k].v;
        if (!dset.equivalent(i, j))
        {
            max_edge = max(max_edge, edges[k].w);
            dset.unite(i, j);
            if (--n_forest == m_forest)
                return max_edge;
        }    
    }
    return max_edge;
}

int main()
{
    int n, m, i, j;

    scanf("%d %d", &m_forest, &n);

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
    WDT max_edge = mst_kruskal(dset, edges, m);
    printf("%.2lf\n", max_edge);
    return 0;
}

