// P1141 01迷宫
// https://www.luogu.org/problemnew/show/P1141


#include <cstdio>

const int MAX_N = 1010;

int n;
char s[MAX_N][MAX_N];            // 输入的地图
int v[MAX_N][MAX_N] = {0};       // 实际上用 id 来标记访问
int answer[MAX_N * MAX_N] = {0}; // 最后的结果

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, int z, int id)
{
    if (x < 1 || x > n || y < 1 || y > n) return;
    if (v[x][y] || s[x][y] != z + '0') return;

    v[x][y] = id;
    answer[id]++;

    for (int i = 0; i < 4; ++i)
        dfs(x + dx[i], y + dy[i], z ^ 1, id);
}

int main()
{
    int m, i, j;
    scanf("%d %d", &n, &m);

    for (i = 1; i <= n; ++i)
        scanf("%s", &s[i][1]);

    int k = 1;  // id
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            if (!v[i][j])
                dfs(i, j, s[i][j] - '0', k++);

    int x, y;
    for (i = 0; i < m; ++i)
    {
        scanf("%d %d", &x, &y);
        printf("%d\n", answer[v[x][y]]);
    }

    return 0;
}