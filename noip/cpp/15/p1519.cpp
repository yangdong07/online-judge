
// P1519 穿越栅栏 Overfencing
// https://www.luogu.org/problemnew/show/P1519

#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_H = 100 + 1;
const int MAX_W = 38 + 1;

int h, w;
char map[MAX_H * 2][MAX_W * 2];
int d1[MAX_H][MAX_W] = {0};
int d2[MAX_H][MAX_W] = {0};

enum DIRECTION { NORTH, EAST, SOUTH, WEST };
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};;
const char bc[] = {'-', '|', '-', '|'};

struct Position 
{
    int x, y;
    Position() {}
    Position(int x, int y): x(x), y(y) {}
    bool block(int d)
    {
        int i = 2 * x - 1 + dx[d];
        int j = 2 * y - 1 + dy[d];
        // printf("(%d %d): %c, %c\n", x, y, map[i][j], bc[d]);
        return map[i][j] == bc[d];
    }
};

int getline(char *s)
{
    int i = 0;
    char c;
    for (c = getchar(); c != '\n' && c != EOF; c = getchar())
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void bfs(Position p, int d[MAX_H][MAX_W])
{
    int i, x, y, z;
    queue<Position> pq;
    pq.push(p);
    d[p.x][p.y] = 1;
    while (!pq.empty())
    {
        Position t = pq.front();
        pq.pop();
        z = d[t.x][t.y];
        for (i = 0; i < 4; ++i)
        {
            if (t.block(i)) continue;
            x = t.x + dx[i], y = t.y + dy[i];
            if (x < 1 || x > h || y < 1 || y > w || d[x][y]) continue;
            d[x][y] = z + 1;
            pq.push(Position(x, y));
        }
    }
}

int main()
{
    int i;
    scanf("%d %d\n", &w, &h);
    for (i = 0; i <= 2 * h; ++i)
        getline(map[i]);

    Position t, start[2];
    int x, y, k = 0;
    for (x = 1; x <= h; ++x)
    {
        if (!Position(x, 1).block(WEST))
            start[k++] = Position(x, 1);
        if (!Position(x, w).block(EAST))
            start[k++] = Position(x, w);
    }
    for (y = 1; y <= w; ++y)
    {
        if (!Position(1, y).block(NORTH))
            start[k++] = Position(1, y);
        if (!Position(h, y).block(SOUTH))
            start[k++] = Position(h, y);
    }

    bfs(start[0], d1);
    bfs(start[1], d2);
    
    int max_s = 0;
    for (x = 1; x <= h; ++x)
        for (y = 1; y <= w; ++y)
            max_s = max(max_s, min(d1[x][y], d2[x][y]));
    printf("%d", max_s);

    return 0;
}