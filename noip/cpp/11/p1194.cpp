
// P1194 买礼物
// https://www.luogu.org/problemnew/show/P1194



#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 501;
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
};

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;   // min first, max last
    }
};


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
    int cost, n, m, i, j;
    int price[MAX_N][MAX_N];

    scanf("%d %d", &cost, &n);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <=n; ++j)
            scanf("%d", &price[i][j]);
    
    Edge *edges = (Edge *)malloc(n * n * sizeof(Edge));
    m = 0;
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <=n; ++j)
        {
            if (price[i][j] == 0 || price[i][j] > cost)
            {
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = cost;
            }
            else
            {
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = price[i][j];
            }
            ++m;
        }

    // vertices id : 1...n
    DisjointSet dset = DisjointSet(n);

    int min_cost = mst_kruskal(dset, edges, m);
    printf("%d\n", min_cost + cost);
    return 0;
}