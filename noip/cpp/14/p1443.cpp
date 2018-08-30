// P1443 马的遍历
// https://www.luogu.org/problemnew/show/P1443

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct position
{
    int x, y;
    position(int x, int y) : x(x), y(y) {}
};

const int MAX_N = 401;
const int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[] = {-2, 2, -1, 1, -2, 2, -1, 1};

int n, m, sx, sy;
int board[MAX_N][MAX_N] = {-1};

void print_board()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            printf("%-5d", board[i][j]);
        printf("\n");
    }
}

void bfs()
{
    int x, y, step;
    queue<position> q;
    board[sx][sy] = 0;
    q.push(position(sx, sy));

    while (!q.empty())
    {
        position p = q.front();
        q.pop();
        step = board[p.x][p.y] + 1;
        for (int i = 0; i < 8; ++i)
        {
            x = p.x + dx[i];
            y = p.y + dy[i];
            if (x < 1 || x > n || y < 1 || y > m || board[x][y] != -1)
                continue;
            board[x][y] = step;
            q.push(position(x, y));
        }
    }
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &sx, &sy);

    memset(board, -1, sizeof(board));

    bfs();
    print_board();
    return 0;
}