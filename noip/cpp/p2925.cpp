// P2925 [USACO08DEC]干草出售Hay For Sale
// https://www.luogu.org/problemnew/show/P2925

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int read_int()
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
    const int MAX_W = 50001;
    int W, n;
    scanf("%d %d", &W, &n);

    int wi, w;
    int dp[MAX_W] = {0};
    for (int i = 0; i < n; ++i)
    {
        wi = read_int();
        // printf("%d\n", wi);
        for (w = W; w >= wi; --w)
            dp[w] = max(dp[w], dp[w - wi] + wi);
        if (dp[W] == W) break;
    }
    printf("%d", dp[W]);
    
    return 0;
}