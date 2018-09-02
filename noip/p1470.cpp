
// P1470 最长前缀 Longest Prefix
// https://www.luogu.org/problemnew/show/P1470

#include <cstdio>
#include <cctype>
#include <cstring>

const int MAX_N = 200001;
const int MAX_M = 201;

int n, m;

char s[MAX_N];
bool dp[MAX_N + 1] = {false};  // dp[i] 表示在第 i 位之前都可以用前缀表示。如果不可以，记为 false。

char dict[MAX_M][11];
int wl[MAX_M] = {0};

bool strncmp(char *a, char *b, int n)
{
    for (int i = 0; i < n; ++i)
        if (a[i] != b[i]) return false;
    return true;
}

bool check_back(int cur)
{
    for (int i = 0; i < m; ++i)
    {
        if (cur >= wl[i] - 1 && dp[cur - wl[i] + 1] &&
            strncmp(&s[cur - wl[i] + 1], dict[i], wl[i]))
            {
                // printf("%d: match: %s\n", cur, dict[i]);
                return true;
            }
    }
    return false;
}

int main()
{
    int i;
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

    dp[0] = true;
    for (i = 0; i < n; ++i)
        dp[i + 1] = check_back(i);

    for (i = n; i >= 0; --i)
        if (dp[i]) break;

    printf("%d\n", i);

    return 0;
}