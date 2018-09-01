
// P1218 [USACO1.5]特殊的质数肋骨 Superprime Rib
// https://www.luogu.org/problemnew/show/P1218

#include <cstdio>

int depth;

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

void dfs(int n, int d)
{
    if (d == depth)
    {
        printf("%d\n", n);
        return;
    }

    n *= 10;
    for (int i = 1; i < 10; i += 2)
        if (is_prime(n + i)) dfs(n + i, d + 1);
}

int main()
{
    scanf("%d", &depth);

    dfs(2, 1);
    dfs(3, 1);
    dfs(5, 1);
    dfs(7, 1);

    return 0;
}