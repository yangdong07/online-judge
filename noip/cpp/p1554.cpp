// P1554 梦中的统计
// https://www.luogu.org/problemnew/show/P1554

#include <cstdio>

int main()
{
    int n, m, i, t;
    scanf("%d %d", &n, &m);
    int count[10] = { };

    for (i = n; i <= m; ++i) {
        t = i;
        while (t) {
            count[t % 10]++;
            t /= 10;
        }
    }
    for (i = 0; i < 10; ++i)
        printf("%d ", count[i]);

}