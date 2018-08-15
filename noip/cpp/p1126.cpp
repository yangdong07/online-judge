// P1126 机器人搬重物
// https://www.luogu.org/problemnew/show/P1126

#include <cstdio>
#include <queue>

using namespace std;

const int MAX_N = 52;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};  // E, S, W, N, clockwise

int n, m, sx, sy, fx, fy;
char sd; //start direction
int maze[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N][4] = { false }; // include 4 direction;

struct position
{
    int x, y; //坐标
    int d;    //方向
    int step; //已移动时间

    position(int x, int y, int d, int step) : x(x), y(y), d(d), step(step) {}
};

bool can_move_to(int x, int y)
{
    if (x < 1 || y < 1 || x + 1 > n || y + 1 > m) return false;

    if (maze[x][y] || maze[x + 1][y] || maze[x][y + 1] || maze[x + 1][y + 1]) return false;

    return true;
}

int bfs()
{
    if (sx == fx && sy == fy)
        return 0;
    int i, j, td;
    queue<position> q;
    visit[sx][sy][sd] = true;
    q.push(position(sx, sy, sd, 0));

    while (!q.empty())
    {
        position p = q.front();
        q.pop();

        p.step++;   // ready for next move
        position t = p;
        // 1:creep, 2:walk, 3:run
        for (i = 1; i <= 3; ++i)
        {
            t.x += dx[t.d];
            t.y += dy[t.d];
            if (!can_move_to(t.x, t.y))
                break;    // robot can not jump, so break
            
            if (t.x == fx && t.y == fy) return t.step;

            if (!visit[t.x][t.y][t.d])
            {
                visit[t.x][t.y][t.d] = true;
                q.push(t);
            }
        }

        // turn left
        t = p;
        t.d = (p.d - 1 + 4) % 4;
        if (!visit[t.x][t.y][t.d])
        {
            visit[t.x][t.y][t.d] = true;
            q.push(t);
        }

        // turn right
        t.d = (p.d + 1) % 4;
        if (!visit[t.x][t.y][t.d])
        {
            visit[t.x][t.y][t.d] = true;
            q.push(t);
        }
    }

    return -1;
}



int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &maze[i][j]);
    
    char d;
    scanf("%d %d %d %d %c", &sx, &sy, &fx, &fy, &d);

    if (d == 'E') sd = 0;
    else if (d == 'S') sd = 1;
    else if (d == 'W') sd = 2;
    else if (d == 'N') sd = 3;

    int step = bfs();

    printf("%d", step);

    return 0;
}