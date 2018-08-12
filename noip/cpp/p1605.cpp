// P1605 迷宫
// https://www.luogu.org/problemnew/show/P1605

#include <iostream>

using namespace std;

const int MAX_N = 21;

int n, m, sx, sy, fx, fy;

int map[MAX_N][MAX_N] = { 0 }; // 0: can pass, 1: obstacle
int v[MAX_N][MAX_N] = { 0 };   // 访问标记

int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int solution = 0;

void walk(int x, int y)
{
    if (x == fx && y == fy)
    {
        solution++;
        return;
    }

    v[x][y] = 1;
    int xx, yy;
    for (int i = 0; i < 4; i++)
    {
        xx = x + dx[i];
        yy = y + dy[i];
        if (!v[xx][yy] && !map[xx][yy])
            walk(xx, yy);
    }
    v[x][y] = 0;
}

int main()
{
    int t;
    cin >> n >> m >> t >> sx >> sy >> fx >> fy;

    int i, j, x, y;

    // 设定边界
    for (i = 0; i <= n + 1; ++i)
        map[i][0] = map[i][m + 1] = 1;
    for (j = 0; j <= m + 1; ++j)
        map[0][j] = map[n + 1][j] = 1;

    for (i = 0; i < t; ++i)
    {
        cin >> x >> y;
        map[x][y] = 1;
    }

    // for (i = 0; i <= n + 1; ++i)
    // {
    //     for (j = 0; j <= m + 1; ++j)
    //         putchar(map[i][j] ? '*' : '.');
    //     putchar('\n');
    // }

    walk(sx, sy);

    cout << solution << endl;
    
    return 0;
}