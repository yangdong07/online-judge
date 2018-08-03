// P4702 取石子
// https://www.luogu.org/problemnew/show/P4702

#include <cstdio>

int main()
{
    int n, i, a, sum = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &a);
        sum += a & 1;
    }
    printf(sum & 1 ? "Alice" : "Bob");
}