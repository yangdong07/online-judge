/*
ID: yesimim1
TASK: ttwo
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("ttwo.out");
    ifstream fin ("ttwo.in");
*/

#include <cstdio>

const int MAX_N = 10;
const int dx[] = {-1, 0, 1, 0}; // N->E->S->W
const int dy[] = {0, 1, 0, -1};

char map[MAX_N][MAX_N + 1];
int visit[MAX_N * MAX_N][MAX_N * MAX_N] = {0};

struct Object
{
    int x, y, d;
    Object() : x(0), y(0), d(0) {}
    Object(int x, int y) : x(x), y(y), d(0) {}
    void move()
    {
        int xx = x + dx[d], yy = y + dy[d];
        if (xx < 0 || xx >= MAX_N || yy < 0 || yy >= MAX_N || map[xx][yy] == '*')
            d = (d + 1) % 4;
        else
            x = xx, y = yy;
    }
    bool meet(const Object &b) const
    {
        return x == b.x && y == b.y;
    }
    int hash() const
    {
        return x * MAX_N + y;
    }
};

int main()
{
    FILE *fin = fopen ("ttwo.in", "r");
    FILE *fout = fopen ("ttwo.out", "w");

    int i, j;
    Object cow, john;
    for (i = 0; i < MAX_N; i++)
    {
        fscanf(fin, "%s", map[i]);
        for (j = 0; j < MAX_N; j++)
        {
            if (map[i][j] == 'C')
                cow = Object(i, j);
            else if (map[i][j] == 'F')
                john = Object(i, j);
        }
    }

    int minutes = 0;
    while (!john.meet(cow))
    {
        if (visit[john.hash()][cow.hash()]++ == 4)
        {
            fprintf(fout, "0\n");
            return 0;
        }
        john.move();
        cow.move();
        minutes++;
    }
    fprintf(fout, "%d\n", minutes);
    return 0;
}