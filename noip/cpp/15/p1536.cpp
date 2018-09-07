
// P1536 村村通
// https://www.luogu.org/problemnew/show/P1536

#include <cstdio>

const int MAX_N = 100010;

int s[MAX_N] = {0};

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

int main()
{
    int n, m, i, x, y;

    int count;

    for (scanf("%d", &n); n; scanf("%d", &n))
    {
        count = 0;
        scanf("%d", &m);
        for (i = 1; i <= n; ++i)
            s[i] = i;

        for (i = 0; i < m; ++i)
        {
            scanf("%d%d", &x, &y);
            unite(x, y);
        }
        for (i = 1; i <= n; ++i)
            if (s[i] == i) ++count;

        printf("%d\n", count - 1);
    }
    return 0;
}