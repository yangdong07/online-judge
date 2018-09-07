
// P3367 【模板】并查集
// https://www.luogu.org/problemnew/show/P3367


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
    int n, m, i, x, y, z;
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; ++i)
        s[i] = 0;

    for (i = 1; i <= m; ++i)
    {
        read_num(z);
        read_num(x);
        read_num(y);
        if (z == 1)
            unite(x, y);
        else if (find(x) == find(y))
            printf("Y\n");
        else
            printf("N\n");
        // for (int k = 0; k <= n; ++k)
        //     printf("%d ", s[k]);
        // printf("\n");
    }
    return 0;
}