
// P1551 亲戚
// https://www.luogu.org/problemnew/show/P1551

#include <cstdio>

const int MAX_N = 100010;

int s[MAX_N] = {0};

int find(int x)
{
    if (s[x] <= 0)
        return x;
    return s[x] = find(s[x]);
}

void unite(int x, int y)
{
    int rx = find(x);
    int ry = find(y);

    if (rx == ry) return;

    if (s[ry] < s[rx]) // y is deeper
        s[rx] = ry;
    else
    {
        if (s[rx] == s[ry])
            s[rx]--;
        s[ry] = rx;
    }
}

int main()
{
    int n, m, p, i, x, y;
    scanf("%d %d %d", &n, &m, &p);

    for (i = 0; i < m; ++i)
    {
        scanf("%d %d", &x, &y);
        unite(x, y);
    }
    for (i = 0; i < p; ++i)
    {
        scanf("%d %d", &x, &y);
        printf(find(x) == find(y) ? "Yes\n" : "No\n");
    }
    return 0;
}