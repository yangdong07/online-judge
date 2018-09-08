
// P1546 最短网络 Agri-Net
// https://www.luogu.org/problemnew/show/P1546


#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 101;

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
    int n, i, j;

    scanf("%d", &n);

    int adjs[MAX_N][MAX_N];
    Edge edges[MAX_N * MAX_N];

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            scanf("%d", &adjs[i][j]);
    
    // edges id : 0...(m - 1)
    int m = 0;
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= n; ++j)
            if (adjs[i][j])
            {
                edges[m].u = i;
                edges[m].v = j;
                edges[m++].w = adjs[i][j];
            }
    
    // vertices id : 1...n
    DisjointSet dset = DisjointSet(n);

    sort(edges, edges + m);

    int min_cost;
    mst_kruskal(dset, edges, m, min_cost);
    printf("%d\n", min_cost);

    return 0;
}

