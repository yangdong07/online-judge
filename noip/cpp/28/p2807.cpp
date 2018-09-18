// P2807 三角形计数
// https://www.luogu.org/problemnew/show/P2807

#include <cstdio>

int main()
{
    const int MAX_N = 500 + 1;
    int a[MAX_N], i;
    a[0] = 0;

    for (i = 1; i < MAX_N; ++i)
        a[i] = a[i - 1] + i * (i + 1) / 2 + i * i / 4;
    
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", a[n]);
    }
    return 0;
}