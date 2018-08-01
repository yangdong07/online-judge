// P1319 压缩技术
// https://www.luogu.org/problemnew/show/P1319

#include <cstdio>

int main()
{
    int n, m, c = 0;
    int i = 1, j;
    scanf("%d", &n);

    for (i = 1; i < n * n; ) {
        scanf("%d", &m);
        for (j = i; j < i + m; ++j) {
            putchar(c + '0');
            if (j % n == 0) putchar('\n');
        }
        c ^= 1;
        i += m;
    }
}