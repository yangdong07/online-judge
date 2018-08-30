// P1434 [SHOI2002]滑雪
// https://www.luogu.org/problemnew/show/P1434

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_INT = 1 << 30;
const int MAX_N = 102;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m;
int map[MAX_N][MAX_N];
int visit[MAX_N][MAX_N] = { 0 };  // 用作标记访问数组，同时记录最大长度 >>> 记忆化搜索

int dfs(int x, int y, int z)
{
    // 越界
    if (x < 1 || x > n || y < 1 || y > m) return 0;
    // 上升
    if (map[x][y] >= z) return 0;
    // 已经做过标记
    if (visit[x][y]) return visit[x][y];

    // 需要搜索
    int height = 0;
    for (int i = 0; i < 4; ++i)
        height = max(height, dfs(x + dx[i], y + dy[i], map[x][y]));
    visit[x][y] = height + 1;
    return visit[x][y];
}

int main()
{
    scanf("%d %d", &n, &m);
    int i, j;
    for (i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            scanf("%d", &map[i][j]);

    int len = 0;
    for (i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            len = max(len, dfs(i, j, MAX_INT));  // MAX_INT 表示从太空中落下来..
    printf("%d", len);

    return 0;
}