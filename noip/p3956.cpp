// P3956 棋盘
// https://www.luogu.org/problemnew/show/P3956

#include <cstdio>

const int MAX_M = 101;
const int INF = 1 << 30;
const int RED = 0;
const int YELLOW = 1;
const int TMP = 2;   // bit '10'

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int m;                     // 地图边长
int map[MAX_M][MAX_M];     // 地图，颜色标记


void relax(int sc, int cost, int x, int y, int c)
{
    if (x < 1 || x > m || y < 1 || y > m) continue;

    int cost2, cc;
    if (!(sc & TMP) && (c == -1))  // color to no color
        


    
}

void relax(int x, int y, int c)
{
    int cost = dist[c][x][y];
    if (cost == INF) return;
    printf("relax %d %d %d, cost %d\n", x, y, c, cost);

    int xx, yy, cc;
    for (int d = 0; d < 4; ++d)
    {
        xx = x + dx[d];
        yy = y + dy[d];
        cc = map[xx][yy];
        if (xx < 1 || xx > m || yy < 1 || yy > m) continue;
        printf("edge (%d:%d:%d) -> (%d:%d:%d)\n", x, y, c, xx, yy, cc);

        if (!(c & TMP) && cc == -1)   // color to no color
        {
            // change color to current color
            cc = TMP + c;
            printf("\trelax (%d:%d:%d) -> %d\n", cc, xx, yy, cost + 2);
            if (dist[cc][xx][yy] > cost + 2)
                dist[cc][xx][yy] = cost + 2;
            
            // change color to flip color
            cc = TMP + c ^ 1;
            printf("\trelax (%d:%d:%d) -> %d\n", cc, xx, yy, cost + 3);
            if (dist[cc][xx][yy] > cost + 3)
                dist[cc][xx][yy] = cost + 3;
        }
        else if (cc != -1)  // has color
        {
            if ((c & 1) ^ cc)   // diff color
            {
                printf("\trelax (%d:%d:%d) -> %d\n", cc, xx, yy, cost + 1);
                if (dist[cc][x][y] > cost + 1)
                    dist[cc][x][y] = cost + 1;
            }
            else
            {
                printf("\trelax (%d:%d:%d) -> %d\n", cc, xx, yy, cost);
                if (dist[cc][x][y] > cost)
                    dist[cc][x][y] = cost;
            }
        }
    }

}

int main()
{
    int n, i, j, k;
    scanf("%d %d", &m, &n);

    // init map
    for (i = 1; i <= m; ++i)
        for (j = 1; j <= m; ++j)
            map[i][j] = -1;
    
    int x, y, color;
    for (k = 0; k < n; ++k)
    {
        scanf("%d %d %d", &x, &y, &color);
        map[x][y] = color;
    }

    // init distance
    for (k = 0; k < 4; ++k)
        for (i = 1; i <= m; ++i)
            for (j = 1; j <= m; ++j)
                dist[k][i][j] = INF;
    
    // bellman-ford algorithm

    dist[map[1][1]][1][1] = 0;
    for (int z = 0; z < m * m; ++z)
        for (k = 0; k < 4; ++k)
            for (i = 1; i <= m; ++i)
                for (j = 1; j <= m; ++j)
                    relax(i, j, k);
    for (k = 0; k < 4; ++k)
        printf("%d ", dist[k][m][m]);

    return 0;
}