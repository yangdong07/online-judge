
// P3366 【模板】最小生成树
// https://www.luogu.org/problemnew/show/P3366

// kruskal 版本

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 5000;
// const int MAX_E = 200000;

struct DisjointSet
{
    int n;
    int s[MAX_N];
    DisjointSet(int n) : n(n)
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
    int size()
    {
        int _size = 0;
        for (int i = 1; i <= n; ++i)
            if (s[i] == i) ++_size;
        return _size;
    }
    void print()
    {
        for (int i = 1; i <= n; ++i)
            printf("%d ", s[i]);
        printf("\n");
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


bool mst_kruskal(DisjointSet &dset, Edge *edges, int m, int &min_cost)
{
    int i, j, k;
    min_cost = 0;

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
    return dset.size() == 1;  // all connected
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

    scanf("%d %d", &n, &m);

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

    sort(edges, edges + m);

    int min_cost;
    if (mst_kruskal(dset, edges, m, min_cost))
        printf("%d\n", min_cost);
    else
        printf("orz\n");
    return 0;
}