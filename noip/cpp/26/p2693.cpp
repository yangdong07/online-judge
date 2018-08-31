
// P2693 [USACO1.3]号码锁 Combination Lock
// https://www.luogu.org/problemnew/show/P2693


#include <cstdio>

int abs(int a) { return a < 0 ? -a : a; }

int n;

bool near(int a, int b)
{
    if (a < b)
        return (b - a) <= 2 || (a + n - b) <= 2;
    else
        return (a - b) <= 2 || (b + n - a) <= 2;
}

bool valid(int a, int b, int c, int code[])
{
    return near(a, code[0]) && near(b, code[1]) && near(c, code[2]);
}


int main()
{
    scanf("%d", &n);

    int i, j, k;
    int a[3], b[3];
    for (i = 0; i < 3; ++i)
        scanf("%d", a + i);
    for (i = 0; i < 3; ++i)
        scanf("%d", b + i);

    int count = 0;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            for (k = 1; k <= n; ++k)
                if (valid(i, j, k, a) || valid(i, j, k, b))
                    count++;
    printf("%d\n", count);

    return 0;
}