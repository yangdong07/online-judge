// P2639 [USACO09OCT]Bessie的体重问题Bessie's We…
// https://www.luogu.org/problemnew/show/P2639

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_W = 45001;
    int W, n;
    scanf("%d %d", &W, &n);

    int wi, w;
    int dp[MAX_W] = {0};
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &wi);
        for (w = W; w >= wi; --w)
            dp[w] = max(dp[w], dp[w - wi] + wi);
    }
    printf("%d", dp[W]);
    
    return 0;
}