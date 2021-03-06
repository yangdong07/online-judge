
// P1930 亚瑟王的宫殿
// https://www.luogu.org/problemnew/show/P1930

#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX_R = 40;
const int MAX_C = 26;
const int MAX_N = MAX_R * MAX_C;
const int INF = 1 << 20;

const int dx_knight[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy_knight[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int dx_king[] = {0, 0, 1, 1, 1, 0, -1, -1, -1, 0, 2, 2, 2, 0, -2, -2, -2};
const int dy_king[] = {0, 1, 1, 0, -1, -1, -1, 0, 1, 2, 2, 0, -2, -2, -2, 0, 2};

struct node
{
    int x, y;
    int dd(const int &cx, const int &cy) const // direct distance
    {
        return max(abs(x - cx), abs(y - cy));
    }
    node() {}
    node(int x, int y) : x(x), y(y) {}
};

int R, C;
int dist[MAX_R][MAX_C][MAX_R][MAX_C];

void bfs(int sx, int sy, int d[MAX_R][MAX_C])
{
    int x, y, i, j;
    queue<node> q;
    for (i = 0; i < R; ++i)
        for (j = 0; j < C; ++j)
            d[i][j] = INF;
    d[sx][sy] = 0;
    q.push(node(sx, sy));
    while (!q.empty())
    {
        node n = q.front();
        q.pop();
        for (i = 0; i < 8; ++i)
        {
            x = n.x + dx_knight[i], y = n.y + dy_knight[i];
            if (x < 0 || x >= R || y < 0 || y >= C || d[x][y] < INF) continue;
            d[x][y] = d[n.x][n.y] + 1;
            q.push(node(x, y));
        }
    }
}

bool read_node(node &p)
{
    char c;
    for (c = getchar(); c != EOF; c = getchar())
        if (c >= 'A' && c <= 'Z')
        {
            p.y = c - 'A';
            break;
        }
    if (c == EOF) return false;
    scanf("%d", &p.x);
    --p.x;
    return true;
}

int main()
{
    int i, j, k;
    scanf("%d %d", &R, &C);

    int n = 0;
    node king, knights[MAX_N];
    read_node(king);
    while (read_node(knights[n])) ++n;

    // for (i = 0; i < n; ++i)
    //     printf("%d %d\n", knights[i].x, knights[i].y);
    if (n == 0)
    {
        printf("0\n");
        return 0;
    }

    for (i = 0; i < R; i++)
        for (j = 0; j < C; j++)
            bfs(i, j, dist[i][j]);

    // for (i = 0; i < R; i++)
    // {
    //     for (j = 0; j < C; j++)
    //         printf("%d ", dist[0][0][i][j]);
    //     printf("\n");
    // }


    int min_d = INF, solo, ride, save, total;
    int xx, yy;
    for (i = 0; i < R; ++i)
        for (j = 0; j < C; ++j)
        {
            total = king.dd(i, j);
            // printf("%d %d: %d", i, j, total);
            for (k = 0; k < n; ++k)
                total += dist[i][j][knights[k].x][knights[k].y];
            // printf(" %d\n", total);
            if (total > INF) continue;
            for (k = 0; k < n; ++k)
            {
                save = 0;
                solo = dist[i][j][knights[k].x][knights[k].y] + king.dd(i, j);
                for (int z = 0; z < 17; ++z)
                {
                    xx = king.x + dx_king[z];
                    yy = king.y + dy_king[z];
                    if (xx < 0 || xx >= R || yy < 0 || yy >= C) continue;
                    ride = dist[xx][yy][knights[k].x][knights[k].y]
                        + dist[i][j][xx][yy] + king.dd(xx, yy);
                    save = max(save, solo - ride);
                }
                min_d = min(min_d, total - save);
            }
        }
    printf("%d\n", min_d);

    return 0;
}