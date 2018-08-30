// P2837 晚餐队列安排
// https://www.luogu.org/problemnew/show/P2837

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    int n, i, id;
    scanf("%d", &n);

    int dp1 = 0, dp2 = 0;

    for (i = 0; i < n; ++i)
    {
        scanf("%d", &id);
        dp2 = min(dp1, dp2);
        if (id == 1)
            ++dp2;
        else
            ++dp1;
    }

    printf("%d", min(dp1, dp2));
    return 0;
}