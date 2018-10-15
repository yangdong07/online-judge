// P1026 统计单词个数
// https://www.luogu.org/problemnew/show/P1026

#include <cstdio>
#include <cstring>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void read_text(char s[], int n)
{
    char c;
    for (int i = 0; i < n;)
    {
        c = getchar();
        if (c >= 'a' && c <= 'z') s[i++] = c;
    }
    s[n] = '\0';
}

int main()
{
    const int MAX_N = 6;
    const int MAX_L = 200 + 2;

    char s[MAX_L];
    int p, n, k;  // m words
    scanf("%d %d", &p, &k);
    n = p * 20;
    read_text(s, n);

    char dict[MAX_N][MAX_L];
    int m, wl[MAX_N], i, j;
    scanf("%d", &m);
    for (i = 0; i < m; ++i)
    {
        scanf("%s", dict[i]);
        wl[i] = strlen(dict[i]);
    }

    int wc[MAX_L][MAX_L] = {0};
    int dp[MAX_L][MAX_L] = {0};
    int match;

    // printf("%s\n", s);
    // for (i = 0; i < n; ++i)
    //     printf("%c ", s[i]);
    // printf("\n");

    for (j = n; j > 0; --j)
    {
        for (i = j - 1; i >= 0; --i)
        {
            match = 0;
            for (int z = 0; z < m; ++z)
                if (strncmp(&s[i], dict[z], wl[z]) == 0)
                    match = 1;
            wc[i][j] = wc[i + 1][j] + match;
        }
        // for (i = 0; i < j; ++i)
        //     printf("%d ", wc[i][j]);
        // printf("\n");
    }

    for (i = 0; i < n; ++i)
        for (j = i; j <= n; ++j)
            dp[i][j] = wc[i][j];

    while (--k)
    {
        // printf("%d\n", k);
        for (i = n - 1; i >= 0; --i)
            for (j = i + 1; j <= n; ++j)
                for (int c = i + 1; c + 1 < j; ++c)
                    dp[i][j] = max(dp[i][j], dp[i][c] + wc[c][j]);
    }
    printf("%d", dp[0][n]);
    return 0;
}