// P1162 填涂颜色
// https://www.luogu.org/problemnew/show/P1162



#include <cstdio>

using namespace std;

const int MAX_N = 31;

int n;

int map[MAX_N][MAX_N];
bool v[MAX_N][MAX_N] = { false };  // visit

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};  // ->, <-, ^, v

void dfs(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= n) return;
    if (v[x][y] || map[x][y] == 1) return;

    v[x][y] = true;

    for (int i = 0; i < 4; ++i)
        dfs(x + dx[i], y + dy[i]);
}

int main()
{
    scanf("%d", &n);
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &map[i][j]);

    for (i = 0; i < n; ++i)
    {
        dfs(i, 0);
        dfs(i, n - 1);
        dfs(0, i);
        dfs(n - 1, i);
    }


    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (j > 0)
                putchar(' ');
            if (map[i][j] == 0)
                putchar(v[i][j] ? '0' : '2');
            else
                putchar('1');
        }
        putchar('\n');
    }

    return 0;
}