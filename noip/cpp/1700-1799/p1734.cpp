// P1734 最大约数和
// https://www.luogu.org/problemnew/show/P1734

#include <cstdio>

const int MAX_N = 1001;

int fs[MAX_N] = {0};  // sum of factors

void init(int n)
{
    int i, j;
    for (i = 1; i <= n; ++i)
        for (j = i + i; j <= n; j += i)
            fs[j] += i;
}

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    int n;
    scanf("%d", &n);
    init(n);

    int i, j;
    int dp[MAX_N] = {0};
    // for (i = 0; i <= n; ++i)
    //     printf("%d ", fs[i]);
    for (i = 1; i <= n; ++i)
        for (j = n; j >= i; --j)
            dp[j] = max(dp[j], dp[j - i] + fs[i]);
    
    printf("%d", dp[n]);

    return 0;
}