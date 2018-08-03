// P2955 [USACO09OCT]奇数偶数Even? Odd?
// https://www.luogu.org/problemnew/show/P2955


#include <cstdio>

int main()
{
    int n, i;
    int m;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &m);
        printf(m & 1 ? "odd\n" : "even\n");
    }

}