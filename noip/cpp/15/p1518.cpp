
// P1518 两只塔姆沃斯牛 The Tamworth Two
// https://www.luogu.org/problemnew/show/P1518

#include <cstdio>

const int MAX_SIDE = 10;
const int MAX_N = MAX_SIDE * MAX_SIDE * MAX_SIDE * MAX_SIDE * 4 * 4;
const int dx[] = {-1, 0, 1, 0}; // N->E->S->W
const int dy[] = {0, 1, 0, -1};

char map[MAX_SIDE][MAX_SIDE + 1];

struct Object
{
    int x, y, d;
    Object() : x(0), y(0), d(0) {}
    Object(int x, int y) : x(x), y(y), d(0) {}   // default north;
    void move()
    {
        int xx = x + dx[d], yy = y + dy[d];
        if (xx < 0 || xx >= MAX_SIDE || yy < 0 || yy >= MAX_SIDE || map[xx][yy] == '*')
            d = (d + 1) % 4;
        else
            x = xx, y = yy;
    }
    bool meet(const Object &b) const
    {
        return x == b.x && y == b.y;
    }
};

int main()
{
    int i, j;
    Object cow, john;
    for (i = 0; i < MAX_SIDE; i++)
    {
        scanf("%s", map[i]);
        for (j = 0; j < MAX_SIDE; j++)
        {
            if (map[i][j] == 'C')
                cow = Object(i, j);
            else if (map[i][j] == 'F')
                john = Object(i, j);
        }
    }

    for (int i = 0; i < MAX_N; ++i)
    {
        if (john.meet(cow))
        {
            printf("%d\n", i);
            return 0;
        }
        john.move(), cow.move();
    }
    printf("0\n");
    return 0;
}