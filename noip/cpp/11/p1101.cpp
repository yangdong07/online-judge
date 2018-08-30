// P1101 单词方阵
// https://www.luogu.org/problemnew/show/P1101

#include <cstdio>
#include <cstring>

const int MAX_N = 101;

int n;
char s[MAX_N][MAX_N];
char m[MAX_N][MAX_N] = {0};

const char b[] = "yizhong";
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

void expand(int i, int j)
{
    int len = strlen(b), k;
    int di, dj, ii, jj;
    for (int d = 0; d < 8; ++d)
    {
        di = dx[d]; dj = dy[d];
        ii = i + di * (len - 1);
        jj = j + dj * (len - 1);
        if (ii < 0 || ii >= n || jj < 0 || jj >= n)
            continue;
        ii = i; jj = j;
        for (k = 0; k < len; ++k, ii += di, jj += dj)
            if (s[ii][jj] != b[k]) break;

        if (k == len)
        {
            ii = i; jj = j;
            for (k = 0; k < len; ++k, ii += di, jj += dj)
                m[ii][jj] = b[k];
        }
    }
}

int main()
{
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%s", s[i]);

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            expand(i, j);
    
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (!m[i][j]) m[i][j] = '*';
    
    for (i = 0; i < n; ++i)
        printf("%s\n", m[i]);

    return 0;
}