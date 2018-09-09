
// P2916 [USACO08NOV]安慰奶牛Cheering up the Cow
// https://www.luogu.org/problemnew/show/P2916

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
    int n, m, i, j, k;

    scanf("%d %d", &n, &m);

    const int MAX_N = 10000 + 1;
    const int INF = 1 << 29;
    int weight[MAX_N];  // 点权

    for (i = 1; i <= n; ++i)
        scanf("%d", &weight[i]);

    // vertices id : 1...n
    DisjointSet dset = DisjointSet(n);
    // edges id : 0...(m - 1)
    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    int w;
    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(w);
        edges[k].u = i;
        edges[k].v = j;
        edges[k].w = 2 * w + weight[i] + weight[j];
    }
    int min_cost = mst_kruskal(dset, edges, m);
    int min_weight = INF;
    for (i = 1; i <= n; ++i)
        if (min_weight > weight[i]) min_weight = weight[i];
    printf("%d\n", min_cost + min_weight);
    return 0;
}

