// P2907 [USACO08OPEN]农场周围的道路Roads Around The Farm
// https://www.luogu.org/problemnew/show/P2907

#include <cstdio>


int branch(int n, int k)
{
    if (n <= k)
        return 1;

    if ((n - k) & 1)  // can'not branch
        return 1;

    return branch((n - k) / 2, k) + branch((n + k) / 2, k);
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d", branch(n, k));
}