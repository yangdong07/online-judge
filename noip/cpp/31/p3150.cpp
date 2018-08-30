// P3150 pb的游戏（1）
// https://www.luogu.org/problemnew/show/P3150

#include <cstdio>

int main()
{
    int n, i, num;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &num);
        printf(num & 1 ? "zs wins\n" : "pb wins\n");
    }
}