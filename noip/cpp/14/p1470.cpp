
// P1470 最长前缀 Longest Prefix
// https://www.luogu.org/problemnew/show/P1470

#include <cstdio>
#include <cctype>
#include <cstring>


int main()
{
    const int MAX_N = 200001;
    const int MAX_M = 201;

    int n, m, i;

    char s[MAX_N];
    bool dp[MAX_N] = {false};
    char dict[MAX_M][11];
    int wl[MAX_M];

    for (i = 0;; ++i)
    {
        scanf("%s", dict[i]);
        if (dict[i][0] == '.') break;
        wl[i] = strlen(dict[i]);
    }
    m = i;

    // for (i = 0; i < m; ++i)
    //     printf("%2d: %s\n", wl[i], dict[i]);

    i = 0;
    for (char c = getchar(); c != EOF; c = getchar())
        if (isalpha(c)) s[i++] = c;
    n = i;

    int j, k;
    for (i = 0; i < n; ++i)
    {
        if (i > 0 && !dp[i - 1]) continue;
        for (k = 0; k < m; ++k)
        {
            j = i + wl[k] - 1;
            if (j < n && !dp[j] && strncmp(&s[i], dict[k], wl[k]) == 0)
                dp[j] = true;
        }
    }
    // printf("%s\n", s);
    // for (i = 0; i <= n; ++i)
    //     printf("%d", dp[i]);
    // printf("\n");

    for (i = n - 1; i >= 0; --i)
        if (dp[i]) break;

    printf("%d\n", i + 1);

    return 0;
}