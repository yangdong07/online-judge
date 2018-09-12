
// P2640 神秘磁石
// https://www.luogu.org/problemnew/show/P2640

#include <cstdio>


bool is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main()
{
    int n, k, i;
    bool empty = true;
    scanf("%d %d", &n, &k);
    for (i = 2; i <= n - k; ++i)
        if (is_prime(i) && is_prime(i + k))
        {
            empty = false;
            printf("%d %d\n", i, i + k);
        }
    if (empty)
        printf("empty");
    return 0;
}