
// P1111 修复公路
// https://www.luogu.org/problemnew/show/P1111

#include <cstdio>
#include <algorithm>

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

const int MAX_N = 100000 + 1;
int x[MAX_N], y[MAX_N], t[MAX_N], k[MAX_N];

void read_num(int &num)
{
    char c;
    num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}

bool cmp(int i, int j)
{
    return t[i] < t[j];
}

int main()
{
    int n, m, i;
    scanf("%d%d", &n, &m);

    for (i = 0; i < m; ++i)
    {
        read_num(x[i]);
        read_num(y[i]);
        read_num(t[i]);
        k[i] = i;
    }
    std::sort(k, k + m, cmp);

    DisjointSet dset = DisjointSet(n);

    int count = 0;
    for (i = 0; i < m; ++i)
    {
        if (!dset.equivalent(x[k[i]], y[k[i]]))
        {
            ++count;
            dset.unite(x[k[i]], y[k[i]]);
            if (count == n - 1)
            {
                printf("%d", t[k[i]]);
                return 0;
            }
        }
    }
    
    printf("-1");
    return 0;
}
