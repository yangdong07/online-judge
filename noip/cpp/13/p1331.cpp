
// P1331 海战
// https://www.luogu.org/problemnew/show/P1331

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 1000;

char map[MAX_N][MAX_N + 1];
int color[MAX_N][MAX_N] = {0};

int n, m;
int x1, y1, x2, y2;  //  2 points determine a rectangle
int area;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void dfs(int x, int y, int id)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return;
    if (map[x][y] == '.' || color[x][y])
        return;
    color[x][y] = id;
    x1 = min(x1, x);
    x2 = max(x2, x);
    y1 = min(y1, y);
    y2 = max(y2, y);
    ++area;

    for (int i = 0; i < 4; ++i)
        dfs(x + dx[i], y + dy[i], id);
}

int main()
{
    scanf("%d %d\n", &n, &m);

    int i, j;
    for (i = 0; i < n; ++i)
        scanf("%s", map[i]);
    
    int id = 0;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            if (map[i][j] == '#' && !color[i][j])
            {
                x1 = x2 = i;
                y1 = y2 = j;
                area = 0;
                dfs(i, j, ++id);
                if ((x2 - x1 + 1) * (y2 - y1 + 1) > area)
                {
                    printf("Bad placement.");
                    return 0;
                }
            }
        }
    printf("There are %d ships.", id);
    return 0;
}