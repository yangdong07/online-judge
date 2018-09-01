/*
ID: yesimim1
TASK: castle
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("castle.out");
    ifstream fin ("castle.in");
*/

#include <cstdio>

FILE *fin = fopen("castle.in", "r");
FILE *fout = fopen("castle.out", "w");

const int MAX_N = 52;
int n, m;
int walls[MAX_N][MAX_N];
int mark[MAX_N][MAX_N] = {0}; // 染色

struct Wall
{
    int dx, dy;  // direction
    int c, mask; // char and bit mask
    Wall(int dx, int dy, int c, int mask): dx(dx), dy(dy), c(c), mask(mask) {}
    bool exist(int v) { return mask & v; }
};

struct RealWall
{
    int x, y;
    int c, value;
    RealWall() {}
    RealWall(int x, int y, int c, int value): x(x), y(y), c(c), value(value) {}
};

bool cmp(RealWall &a, RealWall &b)
{
    if (a.value != b.value)
        return a.value > b.value;
    if (a.y != b.y)
        return a.y < b.y;   // farthest to the west
    if (a.x != b.x)
        return a.x > b.x;   // farthest to the south
    // same module
    return a.c == 'N';   // a.c must be 'N' or 'E'
}

Wall wall[4] = 
{
    Wall(0, -1, 'W', 1 << 0),
    Wall(-1, 0, 'N', 1 << 1),
    Wall(0, 1, 'E', 1 << 2),
    Wall(1, 0, 'S', 1 << 3),
};

bool WALL_W(int x) { return wall[0].exist(x); }
bool WALL_N(int x) { return wall[1].exist(x); }
bool WALL_E(int x) { return wall[2].exist(x); }
bool WALL_S(int x) { return wall[3].exist(x); }

void print_castle()
{
    int i, j;
    for (i = 1; i <= m; ++i)
    {
        // print walls
        for (j = 1; j <= n; ++j)
        {
            if (WALL_N(walls[i][j])) fprintf(fout, "####");
            else fprintf(fout, "#   ");
        }
        fprintf(fout, "#\n");
        // print through
        for (j = 1; j <= n; ++j)
        {
            if (WALL_W(walls[i][j])) fprintf(fout, "#   ");
            else fprintf(fout, "    ");
        }
        fprintf(fout, "#\n");
    }
    for (j = 1; j <= n; ++j) fprintf(fout, "####");
    fprintf(fout, "#\n");
}

int dfs(int x, int y, int color)
{
    if (mark[x][y]) return 0;
    mark[x][y] = color;

    int count = 1;

    for (int i = 0; i < 4; ++i)
        if (!wall[i].exist(walls[x][y]))
            count += dfs(x + wall[i].dx, y + wall[i].dy, color);

    return count;
}

int main()
{
    int i, j;
    fscanf(fin, "%d %d", &n, &m);

    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j)
            fscanf(fin, "%d", &walls[i][j]);
    // print_castle();
    
    int color = 1;
    int size[MAX_N * MAX_N] = {0};

    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j)
            if (!mark[i][j])
            {
                size[color] = dfs(i, j, color);
                ++color;
            }
    
    int max_size = 0;
    for (i = 1; i < color; ++i)
        if (max_size < size[i]) max_size = size[i];
        // fprintf(fout, "%d: %d\n", i, size[i]);
    
    // select max
    int c, nc;
    RealWall bestwall = RealWall(0, 0, 0, 0), current;
    for (i = m; i > 0; --i)
        for (j = 1; j <= n; ++j)
        {
            c = mark[i][j];
            for (int k = 0; k < 4; ++k)
            {
                nc = mark[i + wall[k].dx][j + wall[k].dy];
                if (wall[k].exist(walls[i][j]) && c != nc)
                {
                    current = RealWall(i, j, wall[k].c, size[c] + size[nc]);
                    if (cmp(current, bestwall))
                        bestwall = current;
                }
            }
        }
    
    fprintf(fout, "%d\n", color - 1);
    fprintf(fout, "%d\n", max_size);
    fprintf(fout, "%d\n", bestwall.value);
    fprintf(fout, "%d %d %c\n", bestwall.x, bestwall.y, bestwall.c);

    return 0;
}