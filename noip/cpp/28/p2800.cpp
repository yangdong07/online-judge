// P2800 又上锁妖塔
// https://www.luogu.org/problemnew/show/P2800

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }
int min3(int a, int b, int c) { return min(a, min(b, c)); }

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    if (n < 3)
    {
        printf("0");
        return 0;
    }
    int dp1, dp2, dp3, tmp;
    dp1 = read_num();
    dp2 = read_num();
    dp3 = read_num();

    for (i = 3; i < n; ++i)
    {
        tmp = read_num() + min3(dp1, dp2, dp3);
        dp1 = dp2;
        dp2 = dp3;
        dp3 = tmp;
    }
    printf("%d", min3(dp1, dp2, dp3));
    return 0;
}