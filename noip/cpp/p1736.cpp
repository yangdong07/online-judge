// P1736 创意吃鱼法
// https://www.luogu.org/problemnew/show/P1736

#include <cstdio>


int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int min3(int a, int b, int c) { return min(a, min(b, c)); }


int read01()
{
    char c;
    do
        c = getchar();
    while (c != '0' && c != '1');
    return c - '0';
}

int main()
{
    const int MAX_N = 2510;
    int n, m, i, j;
    int a[MAX_N] = {1};
    int s0[MAX_N] = {0};  // up 0s
    int s1[MAX_N] = {0};  // left 0s
    int s2[MAX_N] = {0};  // right 0s
    int dp1[MAX_N] = {0}; // left up dp
    int dp2[MAX_N] = {0}; // right up dp
    int max_s = 0;

    scanf("%d %d", &n, &m);

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= m; ++j)
        {
            s0[j] = a[j] == 0 ? s0[j] + 1 : 0; // prev a[j]
            a[j] = read01();
            s1[j + 1] = a[j] == 0 ? s1[j] + 1 : 0;
        }
        for (j = m; j > 0; --j)
        {
            s2[j - 1] = a[j] == 0 ? s2[j] + 1 : 0;

            if (a[j])
            {
                // update dp1 from right to left;
                dp1[j] = min3(dp1[j - 1], s0[j], s1[j]) + 1;
                max_s = max(max_s, dp1[j]);
            }
            else
                dp1[j] = 0;
        }
        for (j = 1; j <= m; ++j)
            if (a[j])
            {
                // update dp2 from left to right
                dp2[j] = min3(dp2[j + 1], s0[j], s2[j]) + 1;
                max_s = max(max_s, dp2[j]);
            }
            else
                dp2[j] = 0;
    }
    printf("%d\n", max_s);

    return 0;
}